#include <fcntl.h>             
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "surface.h"
#include <linux/fb.h>

int openfb(char *devname,surface_t *sur)
{
    int fd;
    uint32_t color,screen_size;
    struct fb_var_screeninfo survar;
    fd = open(devname, O_RDWR);
    if (ioctl(fd, FBIOGET_VSCREENINFO, &survar) < 0)
        return -1;
    //color =argb565(0,0,0xff,0);
    sur->fd = fd;
    sur->width = survar.xres;
    sur->height = survar.yres;
    sur->virtual_width = survar.xres_virtual;
    sur->virtual_height = survar.yres_virtual;
    sur->xoff = survar.xoffset;
    sur->yoff = survar.yoffset;
    sur->bpp = survar.bits_per_pixel;
    sur->stride = sur->bpp * sur->width >> 3;
    memcpy(&sur->color_key,&color,sur->bpp >> 3);
    screen_size = sur->height * sur->stride;
    sur->buf = mmap(0, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    return fd;
}
