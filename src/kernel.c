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

static inline void outl(unsigned short port, unsigned int val) {
  __asm__ volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

static inline unsigned int inl(unsigned short port) {
  unsigned int ret;
  __asm__ volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
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

/* --- 8x8 bitmap font (ASCII 32-127) --- */

static const unsigned char font8x8[96][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* 32   */
    {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00}, /* 33 ! */
    {0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* 34 " */
    {0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00}, /* 35 # */
    {0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00}, /* 36 $ */
    {0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00}, /* 37 % */
    {0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00}, /* 38 & */
    {0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}, /* 39 ' */
    {0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00}, /* 40 ( */
    {0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00}, /* 41 ) */
    {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00}, /* 42 * */
    {0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00}, /* 43 + */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06}, /* 44 , */
    {0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, /* 45 - */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00}, /* 46 . */
    {0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00}, /* 47 / */
    {0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00}, /* 48 0 */
    {0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00}, /* 49 1 */
    {0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00}, /* 50 2 */
    {0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00}, /* 51 3 */
    {0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00}, /* 52 4 */
    {0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00}, /* 53 5 */
    {0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00}, /* 54 6 */
    {0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00}, /* 55 7 */
    {0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00}, /* 56 8 */
    {0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00}, /* 57 9 */
    {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00}, /* 58 : */
    {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06}, /* 59 ; */
    {0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00}, /* 60 < */
    {0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00}, /* 61 = */
    {0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00}, /* 62 > */
    {0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00}, /* 63 ? */
    {0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00}, /* 64 @ */
    {0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00}, /* 65 A */
    {0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00}, /* 66 B */
    {0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00}, /* 67 C */
    {0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00}, /* 68 D */
    {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00}, /* 69 E */
    {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00}, /* 70 F */
    {0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00}, /* 71 G */
    {0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00}, /* 72 H */
    {0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, /* 73 I */
    {0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00}, /* 74 J */
    {0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00}, /* 75 K */
    {0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00}, /* 76 L */
    {0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00}, /* 77 M */
    {0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00}, /* 78 N */
    {0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00}, /* 79 O */
    {0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00}, /* 80 P */
    {0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00}, /* 81 Q */
    {0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00}, /* 82 R */
    {0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00}, /* 83 S */
    {0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, /* 84 T */
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00}, /* 85 U */
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, /* 86 V */
    {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00}, /* 87 W */
    {0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00}, /* 88 X */
    {0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00}, /* 89 Y */
    {0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00}, /* 90 Z */
    {0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00}, /* 91 [ */
    {0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00}, /* 92 \ */
    {0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00}, /* 93 ] */
    {0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00}, /* 94 ^ */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, /* 95 _ */
    {0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, /* 96 ` */
    {0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00}, /* 97 a */
    {0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00}, /* 98 b */
    {0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00}, /* 99 c */
    {0x38, 0x30, 0x30, 0x3E, 0x33, 0x33, 0x6E, 0x00}, /* 100 d */
    {0x00, 0x00, 0x1E, 0x33, 0x3F, 0x03, 0x1E, 0x00}, /* 101 e */
    {0x1C, 0x36, 0x06, 0x0F, 0x06, 0x06, 0x0F, 0x00}, /* 102 f */
    {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F}, /* 103 g */
    {0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00}, /* 104 h */
    {0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, /* 105 i */
    {0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E}, /* 106 j */
    {0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00}, /* 107 k */
    {0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, /* 108 l */
    {0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00}, /* 109 m */
    {0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00}, /* 110 n */
    {0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00}, /* 111 o */
    {0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F}, /* 112 p */
    {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78}, /* 113 q */
    {0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00}, /* 114 r */
    {0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00}, /* 115 s */
    {0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00}, /* 116 t */
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00}, /* 117 u */
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, /* 118 v */
    {0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00}, /* 119 w */
    {0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00}, /* 120 x */
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F}, /* 121 y */
    {0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00}, /* 122 z */
    {0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00}, /* 123 { */
    {0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00}, /* 124 | */
    {0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00}, /* 125 } */
    {0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* 126 ~ */
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, /* 127 DEL */
};

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
      return -1;
    if (!(s & 0x80))
      return 0;
  }
  return -1;
}

static int ata_wait_drq(void) {
  for (int i = 0; i < 100000; i++) {
    unsigned char s = inb(ATA_STATUS);
    if (s & 0x01)
      return -1;
    if (!(s & 0x80) && (s & 0x08))
      return 0;
  }
  return -1;
}

static int ata_read_sector(unsigned int lba, unsigned short *buf) {
  if (ata_wait() < 0)
    return -1;
  outb(ATA_DRIVE, 0xE0 | ((lba >> 24) & 0x0F));
  outb(ATA_SECT, 1);
  outb(ATA_LBA_LO, lba & 0xFF);
  outb(ATA_LBA_MI, (lba >> 8) & 0xFF);
  outb(ATA_LBA_HI, (lba >> 16) & 0xFF);
  outb(ATA_CMD, 0x20);
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
  outb(ATA_CMD, 0x30);
  if (ata_wait_drq() < 0)
    return -1;
  for (int i = 0; i < 256; i++)
    outw(ATA_DATA, buf[i]);
  outb(ATA_CMD, 0xE7);
  ata_wait();
  return 0;
}


#define FS_MAX_FILES 16
#define FS_MAX_NAME 32
#define FS_MAX_DATA 472
#define FS_MAGIC 0x4F534653

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

typedef struct {
  unsigned int flags;
  unsigned int mem_lower, mem_upper;
  unsigned int boot_device;
  unsigned int cmdline;
  unsigned int mods_count, mods_addr;
  unsigned int syms[4];
  unsigned int mmap_length, mmap_addr;
  unsigned int drives_length, drives_addr;
  unsigned int config_table;
  unsigned int boot_loader_name;
  unsigned int apm_table;
  unsigned int vbe_control_info, vbe_mode_info;
  unsigned short vbe_mode, vbe_interface_seg, vbe_interface_off,
      vbe_interface_len;
  unsigned int framebuffer_addr_lo, framebuffer_addr_hi;
  unsigned int framebuffer_pitch;
  unsigned int framebuffer_width, framebuffer_height;
  unsigned char framebuffer_bpp, framebuffer_type;
} __attribute__((packed)) multiboot_info_t;

static unsigned char *fb;
static unsigned int fb_pitch;
static unsigned int fb_width;
static unsigned int fb_height;
static unsigned char fb_bpp;

#define PCI_ADDR 0xCF8
#define PCI_DATA 0xCFC

static unsigned int pci_read(unsigned char bus, unsigned char dev,
                             unsigned char reg) {
  outl(PCI_ADDR, 0x80000000u | ((unsigned int)bus << 16) |
                     ((unsigned int)dev << 11) | (reg & 0xFC));
  return inl(PCI_DATA);
}

static unsigned int pci_find_vga_bar0(void) {
  for (unsigned int bus = 0; bus < 8; bus++)
    for (unsigned int dev = 0; dev < 32; dev++) {
      if (pci_read(bus, dev, 0) == 0xFFFFFFFF)
        continue;
      if ((pci_read(bus, dev, 8) >> 16) == 0x0300)
        return pci_read(bus, dev, 0x10) & 0xFFFFFFF0;
    }
  return 0;
}

#define BGA_INDEX 0x01CE
#define BGA_DATA 0x01CF

static void bga_write(unsigned short idx, unsigned short val) {
  outw(BGA_INDEX, idx);
  outw(BGA_DATA, val);
}

static void fb_init(void) {
  unsigned int bar0 = pci_find_vga_bar0();
  if (!bar0)
    return;
  bga_write(4, 0x00);
  bga_write(1, 800);
  bga_write(2, 600);
  bga_write(3, 32);
  bga_write(4, 0x41);
  fb = (unsigned char *)bar0;
  fb_pitch = 800 * 4;
  fb_width = 800;
  fb_height = 600;
  fb_bpp = 32;
}

static void fb_putpixel(unsigned int x, unsigned int y, unsigned int rgb) {
  unsigned int *p = (unsigned int *)(fb + y * fb_pitch + x * (fb_bpp >> 3));
  *p = rgb;
}

static void fb_draw(void) {
  if (!fb)
    return;
  for (unsigned int y = 0; y < fb_height; y++)
    for (unsigned int x = 0; x < fb_width; x++) {
      unsigned char r = (unsigned char)(x * 255 / fb_width);
      unsigned char g = (unsigned char)(y * 255 / fb_height);
      unsigned char b = (unsigned char)((x + y) * 255 / (fb_width + fb_height));
      fb_putpixel(x, y, ((unsigned int)r << 16) | ((unsigned int)g << 8) | b);
    }
}

#define CHAR_W 8
#define CHAR_H 8

static unsigned int con_col = 0;
static unsigned int con_row = 0;

static void con_draw_char(unsigned int col, unsigned int row, char c) {
  if (c < 32 || c > 127)
    c = '?';
  const unsigned char *glyph = font8x8[(unsigned char)c - 32];
  unsigned int px = col * CHAR_W;
  unsigned int py = row * CHAR_H;
  for (int y = 0; y < CHAR_H; y++) {
    unsigned char bits = glyph[y];
    for (int x = 0; x < CHAR_W; x++) {
      unsigned int color = (bits & (0x80 >> x)) ? 0xAAAAAA : 0x000000;
      fb_putpixel(px + x, py + y, color);
    }
  }
}

static void con_scroll(void) {
  unsigned int row_bytes = fb_pitch * CHAR_H;
  unsigned int copy_size = fb_pitch * fb_height - row_bytes;
  unsigned char *dst = fb;
  unsigned char *src = fb + row_bytes;
  for (unsigned int i = 0; i < copy_size; i++)
    dst[i] = src[i];
  /* clear last character row */
  unsigned int last = fb_pitch * (fb_height - CHAR_H);
  for (unsigned int i = 0; i < row_bytes; i++)
    fb[last + i] = 0;
  if (con_row > 0)
    con_row--;
}

static void con_putchar(char c) {
  if (!fb)
    return;
  unsigned int cols = fb_width / CHAR_W;
  unsigned int rows = fb_height / CHAR_H;
  if (c == '\r') {
    con_col = 0;
  } else if (c == '\n') {
    con_col = 0;
    con_row++;
  } else if (c == '\b') {
    if (con_col > 0) {
      con_col--;
      con_draw_char(con_col, con_row, ' ');
    }
  } else {
    con_draw_char(con_col, con_row, c);
    con_col++;
    if (con_col >= cols) {
      con_col = 0;
      con_row++;
    }
  }
  while (con_row >= rows)
    con_scroll();
}

static void con_print(const char *s) {
  for (int i = 0; s[i]; i++)
    con_putchar(s[i]);
}

static void con_clear(void) {
  if (!fb)
    return;
  unsigned int total = fb_pitch * fb_height;
  for (unsigned int i = 0; i < total; i++)
    fb[i] = 0;
  con_col = 0;
  con_row = 0;
}

#define KBD_DATA 0x60
#define KBD_STATUS 0x64

static int kbd_shift = 0;
static int kbd_caps = 0;

static const char kbd_map[128] = {
    /* 00 */ 0,
    /* 01 */ 27, /* Esc */
    /* 02 */ '1',
    /* 03 */ '2',
    /* 04 */ '3',
    /* 05 */ '4',
    /* 06 */ '5',
    /* 07 */ '6',
    /* 08 */ '7',
    /* 09 */ '8',
    /* 0A */ '9',
    /* 0B */ '0',
    /* 0C */ '-',
    /* 0D */ '=',
    /* 0E */ '\b',
    /* 0F */ '\t',
    /* 10 */ 'q',
    /* 11 */ 'w',
    /* 12 */ 'e',
    /* 13 */ 'r',
    /* 14 */ 't',
    /* 15 */ 'y',
    /* 16 */ 'u',
    /* 17 */ 'i',
    /* 18 */ 'o',
    /* 19 */ 'p',
    /* 1A */ '[',
    /* 1B */ ']',
    /* 1C */ '\r',
    /* 1D */ 0, /* Left Ctrl */
    /* 1E */ 'a',
    /* 1F */ 's',
    /* 20 */ 'd',
    /* 21 */ 'f',
    /* 22 */ 'g',
    /* 23 */ 'h',
    /* 24 */ 'j',
    /* 25 */ 'k',
    /* 26 */ 'l',
    /* 27 */ ';',
    /* 28 */ '\'',
    /* 29 */ '`',
    /* 2A */ 0, /* Left Shift */
    /* 2B */ '\\',
    /* 2C */ 'z',
    /* 2D */ 'x',
    /* 2E */ 'c',
    /* 2F */ 'v',
    /* 30 */ 'b',
    /* 31 */ 'n',
    /* 32 */ 'm',
    /* 33 */ ',',
    /* 34 */ '.',
    /* 35 */ '/',
    /* 36 */ 0, /* Right Shift */
    /* 37 */ '*',
    /* 38 */ 0, /* Left Alt */
    /* 39 */ ' ',
    /* 3A-7F */ 0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0};

static const char kbd_map_shift[128] = {
    /* 00 */ 0,
    /* 01 */ 27,
    /* 02 */ '!',
    /* 03 */ '@',
    /* 04 */ '#',
    /* 05 */ '$',
    /* 06 */ '%',
    /* 07 */ '^',
    /* 08 */ '&',
    /* 09 */ '*',
    /* 0A */ '(',
    /* 0B */ ')',
    /* 0C */ '_',
    /* 0D */ '+',
    /* 0E */ '\b',
    /* 0F */ '\t',
    /* 10 */ 'Q',
    /* 11 */ 'W',
    /* 12 */ 'E',
    /* 13 */ 'R',
    /* 14 */ 'T',
    /* 15 */ 'Y',
    /* 16 */ 'U',
    /* 17 */ 'I',
    /* 18 */ 'O',
    /* 19 */ 'P',
    /* 1A */ '{',
    /* 1B */ '}',
    /* 1C */ '\r',
    /* 1D */ 0,
    /* 1E */ 'A',
    /* 1F */ 'S',
    /* 20 */ 'D',
    /* 21 */ 'F',
    /* 22 */ 'G',
    /* 23 */ 'H',
    /* 24 */ 'J',
    /* 25 */ 'K',
    /* 26 */ 'L',
    /* 27 */ ':',
    /* 28 */ '"',
    /* 29 */ '~',
    /* 2A */ 0,
    /* 2B */ '|',
    /* 2C */ 'Z',
    /* 2D */ 'X',
    /* 2E */ 'C',
    /* 2F */ 'V',
    /* 30 */ 'B',
    /* 31 */ 'N',
    /* 32 */ 'M',
    /* 33 */ '<',
    /* 34 */ '>',
    /* 35 */ '?',
    /* 36 */ 0,
    /* 37 */ '*',
    /* 38 */ 0,
    /* 39 */ ' ',
    /* 3A-7F */ 0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0};

static char kbd_getchar(void) {
  static int extended = 0;
  while (1) {
    while (!(inb(KBD_STATUS) & 0x01))
      ;
    unsigned char sc = inb(KBD_DATA);

    if (sc == 0xE0) {
      extended = 1;
      continue;
    }

    if (sc & 0x80) { /* break (key release) */
      unsigned char key = sc & 0x7F;
      if (!extended && (key == 0x2A || key == 0x36))
        kbd_shift = 0;
      extended = 0;
      continue;
    }

    if (extended) {
      extended = 0;
      continue;
    } /* skip extended keys */

    if (sc == 0x2A || sc == 0x36) {
      kbd_shift = 1;
      continue;
    }
    if (sc == 0x3A) {
      kbd_caps = !kbd_caps;
      continue;
    }

    char c = kbd_shift ? kbd_map_shift[sc] : kbd_map[sc];

    /* Apply caps lock to letters */
    if (kbd_caps && !kbd_shift && c >= 'a' && c <= 'z')
      c -= 32;
    if (kbd_caps && kbd_shift && c >= 'A' && c <= 'Z')
      c += 32;

    if (c)
      return c;
  }
}

static void con_read_line(char *buf, int max) {
  int i = 0;
  while (i < max - 1) {
    char c = kbd_getchar();
    if (c == '\r' || c == '\n') {
      con_putchar('\n');
      break;
    }
    if (c == '\b') {
      if (i > 0) {
        i--;
        con_putchar('\b');
      }
      continue;
    }
    con_putchar(c);
    buf[i++] = c;
  }
  buf[i] = '\0';
}

void kernel_main(multiboot_info_t *mbi) {
  (void)mbi;
  outb(0x70, inb(0x70) | 0x80);
  outb(0x61, inb(0x61) | 0x0C);

  fb_init();
  fs_load();

  con_print("Type 'help' for a list of commands.\n");

  char buf[256];
  while (1) {
    con_print("> ");
    con_read_line(buf, 256);

    if (streq(buf, "help")) {
      con_print("Commands:\n"
                "  help               show this message\n"
                "  exit               shut down the VM\n"
                "  echo <msg>         print a message\n"
                "  clear              clear the screen\n"
                "  draw               draw to the framebuffer\n"
                "  ls                 list files\n"
                "  cat <file>         print file contents\n"
                "  write <file> <msg> write content to a file\n"
                "  rm <file>          delete a file\n");
    } else if (streq(buf, "draw")) {
      fb_draw();
    } else if (streq(buf, "clear")) {
      con_clear();
    } else if (startswith(buf, "echo")) {
      const char *msg = buf[4] == ' ' ? buf + 5 : "";
      con_print(msg);
      con_print("\n");
    } else if (streq(buf, "ls")) {
      int found = 0;
      for (int i = 0; i < FS_MAX_FILES; i++) {
        if (fs[i].used) {
          con_print(fs[i].name);
          con_print("\n");
          found = 1;
        }
      }
      if (!found)
        con_print("(no files)\n");
    } else if (startswith(buf, "cat ")) {
      const char *name = buf + 4;
      file_t *f = fs_find(name);
      if (f) {
        con_print(f->data);
        con_print("\n");
      } else {
        con_print("No such file: ");
        con_print(name);
        con_print("\n");
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
          con_print("Written.\n");
        else
          con_print("Filesystem full.\n");
      } else {
        con_print("Usage: write <file> <content>\n");
      }
    } else if (startswith(buf, "rm ")) {
      const char *name = buf + 3;
      if (fs_find(name)) {
        fs_delete(name);
        con_print("Deleted.\n");
      } else {
        con_print("No such file: ");
        con_print(name);
        con_print("\n");
      }
    } else if (streq(buf, "exit")) {
      outw(0x604, 0x2000);
      __asm__ volatile("hlt");
    } else if (buf[0] != '\0') {
      con_print("Unknown command: ");
      con_print(buf);
      con_print("\n");
    }
  }
}
