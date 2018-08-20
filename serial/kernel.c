#define COM1 0x3f8

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 cpu_in8(u32 port);
extern void cpu_out8(u32 port, u32 val);

static u8 *textmode = (void *)0xb8000;

static void textmode_putc(u32 c) {
  *textmode++ = c;
  textmode++;
}

static void textmode_puts(const char *s) {
  while (*s) {
    textmode_putc(*s++);
  }
}

static void serial_init(void) {
  // Straight from https://wiki.osdev.org/Serial_Ports
  cpu_out8(COM1 + 1, 0x00); // Disable all interrupts
  cpu_out8(COM1 + 3, 0x80); // Enable DLAB (set baud rate divisor)
  cpu_out8(COM1 + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
  cpu_out8(COM1 + 1, 0x00); //                  (hi byte)
  cpu_out8(COM1 + 3, 0x03); // 8 bits, no parity, one stop bit
  cpu_out8(COM1 + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  cpu_out8(COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

static void serial_wait(void) {
  while (!(0x20 & cpu_in8(COM1 + 5))) {
  }
}

static void serial_putc(u32 c) {
  serial_wait();
  cpu_out8(COM1, c);
}

static void serial_puts(const char *s) {
  while (*s) {
    serial_putc(*s++);
  }
}

void main(void) {
  serial_init();
  serial_puts("Hello serial\n");
  textmode_puts("Hello textmode");
}
