#define PORT 0x3F8 /* COM1 */

static inline void outb(unsigned short port, unsigned char val) {
  __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline unsigned char inb(unsigned short port) {
  unsigned char ret;
  __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
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

void kernel_main(void) {
  serial_init();
  serial_print("Hello, World!\n");
  while (1) {
    serial_putchar(serial_getchar());
  }
}
