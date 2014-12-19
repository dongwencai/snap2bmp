#ifndef __POINT_H__
#define __POINT_H__

#include <stdint.h>
#include "surface.h"

typedef struct{
    uint16_t x,y;
}coord_t;

static inline int set_pixel(surface_t *sur,coord_t point,uint32_t color)
{
    int pos = (sur->xoff + point.x) * sur->stride + (sur->yoff + point.y) * sur->Bpp;
    memcpy(sur->buf + pos,&color,sur->Bpp);
    return 0;
}

static inline int get_pixel(surface_t *sur,coord_t point,uint32_t *color)
{
    int pos = (sur->xoff + point.x) * sur->stride + (sur->yoff + point.y) * sur->Bpp;
    memcpy(color,sur->buf + pos,sur->Bpp);
    return 0;
}
#endif
