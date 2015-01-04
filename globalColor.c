#include <stdint.h>

#define RGBA888TORGBA656(color) (((((color) >> 19) & 0x1f) << 11) \
                                                |((((color) >> 10) & 0x3f) << 5) \
                                            |(((color) >> 3) & 0x1f))
uint32_t color1 =RGBA888TORGBA656(0xd4d0c8);
uint32_t color2 = RGBA888TORGBA656(0xffffff);
uint32_t color3 = RGBA888TORGBA656(0x404040);
uint32_t color4 = RGBA888TORGBA656(0x808080);
