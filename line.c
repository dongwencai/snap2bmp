#include <stdint.h>
#include "line.h"
#include "surface.h"
#include "common.h"
#include "string.h"


int line_horizontal(surface_t *sur,coord_t point,uint16_t len,uint32_t color)
{
    int i,real_len = MIN(len,sur->virtual_width - point.x);
    for(i = sur->xoff + point.x;i < real_len;i ++)
    {
        memcpy(&sur->buf[point.y * sur->stride + i * sur->bpp >> 3],&color,sur->bpp >> 3);
    }
}

int line_vertical(surface_t *sur,coord_t point,uint16_t len ,uint32_t color)
{
   int i,real_len = MIN(len,sur->virtual_height - point.y); 
   for(i = sur->yoff;i < real_len;i ++)
   {
       memcpy(&sur->buf[point.y * sur->stride + i * sur->bpp >> 3],&color,sur->bpp >> 3);
         
   }
}

int line(surface_t *sur,coord_t point0,coord_t point1,uint32_t color)
{

}

