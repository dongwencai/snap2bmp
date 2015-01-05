#include <stdint.h>
#include "line.h"
#include "surface.h"
#include "common.h"
#include "string.h"
int line_horizontal(surface_t *sur,int x0,int y0,uint16_t len,uint32_t color)
{
    int i,real_len = MIN(len,sur->virtual_width - x0);
    for(i = 0;i < real_len;i ++)
    {
        set_pixel(sur,x0 + i,y0,color);
    }
}
int line_vertical(surface_t *sur,int x0,int y0,uint16_t len ,uint32_t color)
{
    int i,real_len = MIN(len,sur->virtual_height - y0);
    for(i = 0;i < real_len;i ++)
    {
        set_pixel(sur,x0,y0 + i,color);
    }
}
int line(surface_t *sur,int x0,int y0,int x1,int y1,uint32_t color)
{
    if(x0 != x1 && y0 != y1)
    {
       int ax = x0 < x1 ? 1 : -1;
       int ay = y0 < y1 ? 1 : -1;
       int k = ABS(y0 - y1 << 10) / ABS(x0 - x1);
       int i,rx,ry;
       coord_t cr;
       if(k < 1024)
       {
           for(i = x0;i != x1 + ax;i += ax)
           {
               ry = y0 + ((k * ABS(i - x0) + 512) >> 10) * ay;
               set_pixel(sur,i,ry,color);
           }
       }
       else
       {
           for(i = y0;i != y1 + ay;i += ay)
           {
               rx = x0 + (((ABS(i - y0) << 10) + 512) / k) * ax;
               set_pixel(sur,rx,i,color);
           }
       }
    }
    else if(x0 == x1)
    {
       int real_len = ABS(y0 - y1) + 1; 
       if(y0 < y1)
           line_vertical(sur,x0,y0,real_len,color);
       else
           line_vertical(sur,x1,y1,real_len,color);
    }
    else
    {
       int real_len = ABS(x0 - x1) + 1; 
       if(x0 < x1)
           line_horizontal(sur,x0,y0,real_len,color);
       else
           line_horizontal(sur,x1,y1,real_len,color);
    }
}
