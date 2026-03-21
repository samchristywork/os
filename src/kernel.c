#define PORT 0x3F8 /* COM1 */

static inline void outb(unsigned short port, unsigned char val) {
  __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline unsigned char inb(unsigned short port) {
  unsigned char ret;
  __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

static inline void outw(unsigned short port, unsigned short val) {
  __asm__ volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

static inline unsigned short inw(unsigned short port) {
  unsigned short ret;
  __asm__ volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

static void serial_init(void) {
  outb(PORT + 1, 0x00); // disable interrupts
  outb(PORT + 3, 0x80); // enable DLAB
  outb(PORT + 0, 0x03); // baud rate divisor low byte (38400)
  outb(PORT + 1, 0x00); // baud rate divisor high byte
  outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
  outb(PORT + 2, 0xC7); // enable FIFO
  outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

static void serial_putchar(char c) {
  while ((inb(PORT + 5) & 0x20) == 0)
    ;
  outb(PORT, c);
}

static void serial_print(const char *str) {
  for (int i = 0; str[i] != '\0'; i++)
    serial_putchar(str[i]);
}

static char serial_getchar(void) {
  while ((inb(PORT + 5) & 0x01) == 0)
    ;
  return inb(PORT);
}

static int streq(const char *a, const char *b) {
  while (*a && *a == *b) {
    a++;
    b++;
  }
  return *a == *b;
}

static int startswith(const char *str, const char *prefix) {
  while (*prefix)
    if (*str++ != *prefix++)
      return 0;
  return 1;
}

static int strlen(const char *s) {
  int n = 0;
  while (s[n])
    n++;
  return n;
}

static void strcpy(char *dst, const char *src) {
  while ((*dst++ = *src++))
    ;
}

static void read_line(char *buf, int max) {
  int i = 0;
  while (i < max - 1) {
    char c = serial_getchar();
    if (c == '\r' || c == '\n') {
      serial_print("\r\n");
      break;
    }
    if ((c == '\b' || c == 127) && i > 0) {
      i--;
      serial_print("\b \b");
      continue;
    }
    serial_putchar(c);
    buf[i++] = c;
  }
  buf[i] = '\0';
}

#define ATA_DATA 0x1F0
#define ATA_SECT 0x1F2
#define ATA_LBA_LO 0x1F3
#define ATA_LBA_MI 0x1F4
#define ATA_LBA_HI 0x1F5
#define ATA_DRIVE 0x1F6
#define ATA_CMD 0x1F7
#define ATA_STATUS 0x1F7

static int ata_wait(void) {
  for (int i = 0; i < 100000; i++) {
    unsigned char s = inb(ATA_STATUS);
    if (s == 0xFF)
      return -1; // no drive
    if (!(s & 0x80))
      return 0; // BSY cleared
  }
  return -1; // timeout
}

static int ata_wait_drq(void) {
  for (int i = 0; i < 100000; i++) {
    unsigned char s = inb(ATA_STATUS);
    if (s & 0x01)
      return -1; // ERR
    if (!(s & 0x80) && (s & 0x08))
      return 0; // BSY=0, DRQ=1
  }
  return -1; // timeout
}

static int ata_read_sector(unsigned int lba, unsigned short *buf) {
  if (ata_wait() < 0)
    return -1;
  outb(ATA_DRIVE, 0xE0 | ((lba >> 24) & 0x0F));
  outb(ATA_SECT, 1);
  outb(ATA_LBA_LO, lba & 0xFF);
  outb(ATA_LBA_MI, (lba >> 8) & 0xFF);
  outb(ATA_LBA_HI, (lba >> 16) & 0xFF);
  outb(ATA_CMD, 0x20); // READ SECTORS
  if (ata_wait_drq() < 0)
    return -1;
  for (int i = 0; i < 256; i++)
    buf[i] = inw(ATA_DATA);
  return 0;
}

static int ata_write_sector(unsigned int lba, unsigned short *buf) {
  if (ata_wait() < 0)
    return -1;
  outb(ATA_DRIVE, 0xE0 | ((lba >> 24) & 0x0F));
  outb(ATA_SECT, 1);
  outb(ATA_LBA_LO, lba & 0xFF);
  outb(ATA_LBA_MI, (lba >> 8) & 0xFF);
  outb(ATA_LBA_HI, (lba >> 16) & 0xFF);
  outb(ATA_CMD, 0x30); // WRITE SECTORS
  if (ata_wait_drq() < 0)
    return -1;
  for (int i = 0; i < 256; i++)
    outw(ATA_DATA, buf[i]);
  outb(ATA_CMD, 0xE7); // FLUSH CACHE
  ata_wait();
  return 0;
}

/* file_t is exactly 512 bytes: 32 + 472 + 4 + 4 = 512, one sector per file. */
#define FS_MAX_FILES 16
#define FS_MAX_NAME 32
#define FS_MAX_DATA 472
#define FS_MAGIC 0x4F534653 /* "OSFS" */

typedef struct {
  char name[FS_MAX_NAME];
  char data[FS_MAX_DATA];
  int size;
  int used;
} file_t;

static file_t fs[FS_MAX_FILES];

static file_t *fs_find(const char *name) {
  for (int i = 0; i < FS_MAX_FILES; i++)
    if (fs[i].used && streq(fs[i].name, name))
      return &fs[i];
  return 0;
}

static file_t *fs_alloc(void) {
  for (int i = 0; i < FS_MAX_FILES; i++)
    if (!fs[i].used)
      return &fs[i];
  return 0;
}

/* LBA 0: magic sector. LBA 1-16: one file_t per sector. */

static void fs_load(void) {
  static unsigned short magic_buf[256];
  if (ata_read_sector(0, magic_buf) < 0)
    return;
  unsigned int magic =
      (unsigned int)magic_buf[0] | ((unsigned int)magic_buf[1] << 16);
  if (magic != FS_MAGIC)
    return;
  for (int i = 0; i < FS_MAX_FILES; i++)
    if (ata_read_sector(1 + i, (unsigned short *)&fs[i]) < 0)
      return;
}

static void fs_flush(void) {
  static unsigned short magic_buf[256];
  magic_buf[0] = FS_MAGIC & 0xFFFF;
  magic_buf[1] = FS_MAGIC >> 16;
  if (ata_write_sector(0, magic_buf) < 0)
    return;
  for (int i = 0; i < FS_MAX_FILES; i++)
    if (ata_write_sector(1 + i, (unsigned short *)&fs[i]) < 0)
      return;
}

static int fs_write(const char *name, const char *data) {
  file_t *f = fs_find(name);
  if (!f) {
    f = fs_alloc();
    if (!f)
      return 0;
    strcpy(f->name, name);
    f->used = 1;
  }
  int len = strlen(data);
  if (len >= FS_MAX_DATA)
    len = FS_MAX_DATA - 1;
  for (int i = 0; i < len; i++)
    f->data[i] = data[i];
  f->data[len] = '\0';
  f->size = len;
  fs_flush();
  return 1;
}

static void fs_delete(const char *name) {
  file_t *f = fs_find(name);
  if (f) {
    f->used = 0;
    fs_flush();
  }
}

#define VGA_BUF ((unsigned short *)0xB8000)
#define VGA_W 80
#define VGA_H 25

static void vga_set(int x, int y, char c, unsigned char attr) {
  VGA_BUF[y * VGA_W + x] = (unsigned short)(unsigned char)c | ((unsigned short)attr << 8);
}

static void vga_draw(void) {
  static const unsigned char colors[] = { 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14 };
  int ncolors = 12;

  for (int y = 0; y < VGA_H; y++) {
    unsigned char bg = colors[y % ncolors];
    for (int x = 0; x < VGA_W; x++)
      vga_set(x, y, ' ', (unsigned char)(bg << 4));
  }

  const char *msg = "Hello from VGA!";
  int len = strlen(msg);
  int cx = (VGA_W - len) / 2;
  int cy = VGA_H / 2;
  for (int i = 0; i < len; i++)
    vga_set(cx + i, cy, msg[i], 0x0F);
}

void kernel_main(void) {
  outb(0x70, inb(0x70) | 0x80); // disable NMI via CMOS
  outb(0x61, inb(0x61) | 0x0C); // disable IOCHK# and SERR# NMI sources
  serial_init();
  fs_load();
  serial_print("Type 'help' for a list of commands.\r\n");

  char buf[256];
  while (1) {
    serial_print("> ");
    read_line(buf, 256);

    if (streq(buf, "help")) {
      serial_print("Commands:\r\n"
                   "  help               show this message\r\n"
                   "  echo <msg>         print a message\r\n"
                   "  clear              clear the screen\r\n"
                   "  ls                 list files\r\n"
                   "  cat <file>         print file contents\r\n"
                   "  write <file> <msg> write content to a file\r\n"
                   "  rm <file>          delete a file\r\n");
    } else if (streq(buf, "clear")) {
      serial_print("\033[2J\033[H");
    } else if (startswith(buf, "echo")) {
      const char *msg = buf[4] == ' ' ? buf + 5 : "";
      serial_print(msg);
      serial_print("\r\n");
    } else if (streq(buf, "ls")) {
      int found = 0;
      for (int i = 0; i < FS_MAX_FILES; i++) {
        if (fs[i].used) {
          serial_print(fs[i].name);
          serial_print("\r\n");
          found = 1;
        }
      }
      if (!found)
        serial_print("(no files)\r\n");
    } else if (startswith(buf, "cat ")) {
      const char *name = buf + 4;
      file_t *f = fs_find(name);
      if (f) {
        serial_print(f->data);
        serial_print("\r\n");
      } else {
        serial_print("No such file: ");
        serial_print(name);
        serial_print("\r\n");
      }
    } else if (startswith(buf, "write ")) {
      char *name = buf + 6;
      char *content = name;
      while (*content && *content != ' ')
        content++;
      if (*content == ' ') {
        *content = '\0';
        content++;
        if (fs_write(name, content))
          serial_print("Written.\r\n");
        else
          serial_print("Filesystem full.\r\n");
      } else {
        serial_print("Usage: write <file> <content>\r\n");
      }
    } else if (startswith(buf, "rm ")) {
      const char *name = buf + 3;
      if (fs_find(name)) {
        fs_delete(name);
        serial_print("Deleted.\r\n");
      } else {
        serial_print("No such file: ");
        serial_print(name);
        serial_print("\r\n");
      }
    } else if (buf[0] != '\0') {
      serial_print("Unknown command: ");
      serial_print(buf);
      serial_print("\r\n");
    }
  }
}
