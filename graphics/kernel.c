typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

static u32 *screen;
static u32 screen_width;
static u32 screen_height;

static void multiboot_parse_framebuffer(u8 *bytes, u32 nbyte) {
  if (nbyte >= 24) {
    screen = (void *)(*(u32 *)(bytes + 8));
    screen_width = *(u32 *)(bytes + 20);
    screen_height = *(u32 *)(bytes + 24);
  }
}

static void multiboot_parse(u8 *bytes) {
  u8 *lim = bytes + *(u32 *)bytes;
  bytes += 8;
  while (bytes < lim) {
    u32 type = *(u32 *)bytes;
    u32 nbyte = *(u32 *)(bytes + 4);
    if (type == 8) {
      multiboot_parse_framebuffer(bytes, nbyte);
    }
    bytes += (nbyte + 7) & ~7;
  }
}

static void display_hack(void) {
  u32 y, x;
  u32 *pixelp = screen;
  for (y = 0; y < screen_height; y++) {
    for (x = 0; x < screen_width; x++) {
      *pixelp++ = y ^ x;
    }
  }
}

void main(u32 magic, u8 *multiboot) {
  (void)magic;
  multiboot_parse(multiboot);
  display_hack();
}
