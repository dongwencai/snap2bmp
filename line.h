#ifndef __LINE_H__
#define __LINE_H__
#include <stdint.h>
#include "surface.h"
#include "point.h"

extern int line_horizontal(surface_t *sur,int x0,int y0,uint16_t len,uint32_t color);

extern int line_vertical(surface_t *sur,int x0,int y0,uint16_t len ,uint32_t color);

extern int line(surface_t *sur,int x0,int y0,int x1,int y1,uint32_t color);
#endif
