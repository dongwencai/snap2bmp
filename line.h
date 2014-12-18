#ifndef __LINE_H__
#define __LINE_H__
#include <stdint.h>
#include "surface.h"

typedef struct{
    uint16_t x,y;
}coord_t;

extern int line_horizontal(surface_t *sur,coord_t point,uint16_t len,uint32_t color);

extern int line_vertical(surface_t *sur,coord_t point,uint16_t len ,uint32_t color);

extern int line(surface_t *sur,coord_t point0,coord_t point1,uint32_t color);
#endif
