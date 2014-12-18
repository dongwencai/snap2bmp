#ifndef __SURFACE_H__
#define __SURFACE_H__
#include <stdint.h>

typedef struct {
    int fd;
    void *buf;
    int bpp;
    int width;
    int height;
    int xoff;
    int yoff;
    int virtual_width;
    int virtual_height;
    int stride;
    uint32_t color_key;
}surface_t;

extern int openfb(char *devname,surface_t *sur);

#endif
