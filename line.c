#include <stdint.h>
#include "line.h"
#include "surface.h"
#include "common.h"
#include "string.h"
int line_horizontal(surface_t *sur,coord_t point,uint16_t len,uint32_t color)
{
    int i,real_len = MIN(len,sur->virtual_width - point.x);
    coord_t cr = point;
    for(i = 0;i < real_len;i ++)
    {
        cr.x = point.x + i;
        set_pixel(sur,cr,color);
    }
}
int line_vertical(surface_t *sur,coord_t point,uint16_t len ,uint32_t color)
{
    int i,real_len = MIN(len,sur->virtual_height - point.y);
    coord_t cr = point;
    for(i = 0;i < real_len;i ++)
    {
        cr.y = point.y + i;
        set_pixel(sur,cr,color);
    }
}
int line(surface_t *sur,coord_t point0,coord_t point1,uint32_t color)
{
    if(point0.x != point1.x && point0.y != point1.y)
    {
        
    }
    else if(point0.x == point1.x)
    {
       int real_len = ABS(point0.y - point1.y) + 1; 
       coord_t point = point0.y < point1.y ? point0 : point1;
       line_vertical(sur,point,real_len,color);
    }
    else
    {
       int real_len = ABS(point0.x - point1.x) + 1; 
       coord_t point = point0.x < point1.x ? point0 : point1;
       line_horizontal(sur,point,real_len,color);
    }
}
