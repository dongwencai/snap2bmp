#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__
#include "surface.h"
#include "point.h"

typedef struct{
    coord_t p0,p1;
}rect_t;

extern int rectangle(surface_t *sur,rect_t rect,uint32_t bc,uint32_t fc);
#endif
