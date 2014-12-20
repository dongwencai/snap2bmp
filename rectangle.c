#include "surface.h"
#include <stdint.h>
#include "point.h"
#include "line.h"

int rectangle(surface_t *sur,coord_t p0,coord_t p1,uint32_t bc,uint32_t fc)
{
    int nx,ny;
    coord_t point = p0;
    if(fc)
    {
        for(ny = p0.y;ny <= p1.y;ny ++)
        {
            point.y = ny;
            line_horizontal(sur,point,p1.x - p0.x + 1,fc);
        }
    }
    if(bc)
    {
        line_horizontal(sur,p0,p1.x - p0.x + 1,bc);
        line_vertical(sur,p0,p1.y - p0.y + 1,bc);
        point.x = p0.x;
        point.y = p1.y;
        line_horizontal(sur,point,p1.x - p0.x + 1,bc);
        point.x = p1.x;
        point.y = p0.y;
        line_vertical(sur,point,p1.y - p0.y + 1,bc);

    }
}
