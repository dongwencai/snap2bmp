#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__
#include "surface.h"
#include "point.h"

#define INAREA(pt,rect) (pt.x >= rect.p0.x && pt.x <= rect.p1.x && pt.y >= rect.p0.y && pt.y <= rect.p1.y)

typedef struct{
    coord_t p0,p1;
}rect_t;

extern int rectangle(surface_t *sur,rect_t rect,uint32_t bc,uint32_t fc);
#endif
