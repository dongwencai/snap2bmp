#include "surface.h"
#include "point.h"
#include <math.h>
#include "common.h"
#include "line.h"

#define PI 3.141592654

int arc(surface_t *sur,double start_angle,double end_angle,coord_t o,int r,uint32_t bc,uint32_t fc)
{
    double start_arc,end_arc;
    int nsx,nsy,nex,ney;
    coord_t point0,point1;
    start_arc = start_angle * PI / 180;
    end_arc = end_angle * PI / 180;
    nsy = (ABS(sin(start_arc) * r) + 0.5);   
    nsx = (ABS(cos(start_arc) * r) + 0.5);   
    ney = (ABS(sin(end_arc) * r) + 0.5);   
    nex = (ABS(cos(end_arc) * r) + 0.5);   
    nsy = start_angle < 180 ? (o.y - nsy) : (o.y + nsy);
    nsx = (start_angle < 90 || start_angle > 270) ? (o.x + nsx) : (o.x - nsx);
    ney = end_angle < 180 ? (o.y - ney) : (o.y + ney);
    nex = (end_angle < 90 || end_angle > 270) ? (o.x + nex) : (o.x - nex);
    point0.x = nsx;
    point0.y = nsy;
    point1.x = nex;
    point1.y = ney;
    line(sur,o,point0,bc);
    line(sur,o,point1,bc);
}
int circle(surface_t *sur,coord_t o,int r,uint32_t bc,uint32_t fc)
{
    int i,x,y;
    coord_t point0,point1;
    if(fc)
    {
        for(x = 0;x < r; x ++)
        {
            y = sqrt(r * r - x * x) + 0.5;
            point0.x = o.x + x;
            point0.y = o.y + y;
            point1.x = o.x + x;
            point1.y = o.y - y;
            line(sur,point0,point1,fc);
            point0.x = o.x - x;
            point0.y = o.y - y;
            line(sur,point0,point1,fc);
            point1.x = o.y - x;
            point1.y = o.y + y;
            line(sur,point0,point1,fc);
            point0.x = o.x + x;
            point0.y = o.y + y;
            line(sur,point0,point1,fc);
        }
        for(y = 0;y < r; y ++)
        {
            x = sqrt(r * r - y * y) + 0.5;

            point0.x = o.x + x;
            point0.y = o.y + y;
            point1.x = o.x + x;
            point1.y = o.y - y;
            line(sur,point0,point1,fc);
            point0.x = o.x - x;
            point0.y = o.y - y;
            line(sur,point0,point1,fc);
            point1.x = o.y - x;
            point1.y = o.y + y;
            line(sur,point0,point1,fc);
            point0.x = o.x + x;
            point0.y = o.y + y;
            line(sur,point0,point1,fc);

        }
    }
    if(bc)
    {
        for(x = 0;x < r; x ++)
        {
            y = sqrt(r * r - x * x) + 0.5;
            point0.x = o.x + x;
            point0.y = o.y + y;
            set_pixel(sur,point0,bc);
            point0.y = o.y - y;
            set_pixel(sur,point0,bc);
            point0.x = o.x - x;
            set_pixel(sur,point0,bc);
            point0.y = o.y + y;
            set_pixel(sur,point0,bc);
        }
        for(y = 0;y < r; y ++)
        {
            x = sqrt(r * r - y * y) + 0.5;
            point0.x = o.x + x;
            point0.y = o.y + y;
            set_pixel(sur,point0,bc);
            point0.y = o.y - y;
            set_pixel(sur,point0,bc);
            point0.x = o.x - x;
            set_pixel(sur,point0,bc);
            point0.y = o.y + y;
            set_pixel(sur,point0,bc);
        }
    }
}
