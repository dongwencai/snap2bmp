#include "surface.h"
#include "point.h"
#include <math.h>
#include "common.h"
#include "line.h"

#define PI 3.141592654
int arc(surface_t *sur,double start_angle,double end_angle,int ox,int oy,int r,uint32_t bc,uint32_t fc)
{
    double start_arc,end_arc,a,b,c,angle0,angle1;
    int x,y,nsx,nsy,nex,ney,direct,sk,ek;
    start_arc = start_angle * PI / 180;
    end_arc = end_angle * PI / 180;
    nsy = (ABS(sin(start_arc) * r) + 0.5);   
    nsx = (ABS(cos(start_arc) * r) + 0.5);   
    ney = (ABS(sin(end_arc) * r) + 0.5);   
    nex = (ABS(cos(end_arc) * r) + 0.5);   
    nsy = start_angle < 180 ? (oy - nsy) : (oy + nsy);
    nsx = (start_angle < 90 || start_angle > 270) ? (ox + nsx) : (ox - nsx);
    ney = end_angle < 180 ? (oy - ney) : (oy + ney);
    nex = (end_angle < 90 || end_angle > 270) ? (ox + nex) : (ox - nex);
    direct = start_angle < end_angle ? 1 : 0;    
    angle0 = MIN(start_angle,end_angle);
    angle1 = MAX(start_angle,end_angle);
    sk = (nsy - oy) / (nsx - ox);
    if(bc)
    {
        for(x = 0;x < r; x ++)
        {
            y = sqrt(r * r - x * x) + 0.5;
            b = atan2(y,x) * 180 / PI ;
            a = 360 - b;
            if((a >= angle0 && a <= angle1) == direct)
                line(sur,ox,oy,ox + x,oy + y,fc);
            a = b;
            if((a >= angle0 && a <= angle1) == direct)
                line(sur,ox,oy,ox + x,oy - y,fc);
            a = 180 - b;
            if((a >= angle0 && a <= angle1) == direct)
                line(sur,ox,oy,ox -x,oy - y,fc);
            a = 180 + b;
            if((a >= angle0 && a <= angle1) == direct)
                line(sur,ox,oy,ox - x,oy + y,fc);
        }
        for(y = 0;y < r; y ++)
        {
            x = sqrt(r * r - y * y) + 0.5;
            b = atan2(y,x) * 180 / PI;
            a = 360 - b;
            if((a >= angle0 && a <= angle1) == direct)
                line(sur,ox,oy,ox + x,oy + y,fc);
            a = b;
            if((a >= angle0 && a <= angle1) == direct)
                line(sur,ox,oy,ox + x,oy - y,fc);
            a = 180 - b;
            if((a >= angle0 && a <= angle1) == direct)
                line(sur,ox,oy,ox -x,oy - y,fc);
            a = 180 + b;
            if((a >= angle0 && a <= angle1) == direct)
                line(sur,ox,oy,ox - x,oy + y,fc);
        }

    }
    if(fc)
    {
        line(sur,ox,oy,nsx,nsy,bc);
        line(sur,ox,oy,nex,ney,bc);
        for(x = 0;x < r; x ++)
        {
            y = sqrt(r * r - x * x) + 0.5;
            b = atan2(y,x) * 180 / PI ;
            a = 360 - b;
            if((a >= angle0 && a <= angle1) == direct)
                set_pixel(sur,ox + x,oy + y,bc);
            a = b;
            if((a >= angle0 && a <= angle1) == direct)
                set_pixel(sur,ox + x,oy - y,bc);
            a = 180 - b;
            if((a >= angle0 && a <= angle1) == direct)
                set_pixel(sur,ox -x,oy - y,bc);
            a = 180 + b;
            if((a >= angle0 && a <= angle1) == direct)
                set_pixel(sur,ox - x,oy + y,bc);
        }
        for(y = 0;y < r; y ++)
        {
            x = sqrt(r * r - y * y) + 0.5;
            b = atan2(y,x) * 180 / PI;
            a = 360 - b;
            if((a >= angle0 && a <= angle1) == direct)
                set_pixel(sur,ox + x,oy + y,bc);
            a = b;
            if((a >= angle0 && a <= angle1) == direct)
                set_pixel(sur,ox + x,oy - y,bc);
            a = 180 - b;
            if((a >= angle0 && a <= angle1) == direct)
                set_pixel(sur,ox -x,oy - y,bc);
            a = 180 + b;
            if((a >= angle0 && a <= angle1) == direct)
                set_pixel(sur,ox - x,oy + y,bc);
        }
    }
}
int circle(surface_t *sur,int ox,int oy,int r,uint32_t bc,uint32_t fc)
{
    int i,x,y;
    coord_t point0,point1;
    if(fc)
    {
        for(x = 0;x < r; x ++)
        {
            y = sqrt(r * r - x * x) + 0.5;
            line(sur,ox + x,oy + y,ox +x,oy - y,fc);
            line(sur,ox - x,oy - y,ox + x,oy - y,fc);
            line(sur,ox - x,oy - y,ox - x,oy + y,fc);
            line(sur,ox + x,oy + y,ox - x,oy + y,fc);
        }
        for(y = 0;y < r; y ++)
        {
            x = sqrt(r * r - y * y) + 0.5;
            line(sur,ox + x,oy + y,ox +x,oy - y,fc);
            line(sur,ox - x,oy - y,ox + x,oy - y,fc);
            line(sur,ox - x,oy - y,ox - x,oy + y,fc);
            line(sur,ox + x,oy + y,ox - x,oy + y,fc);
        }
    }
    if(bc)
    {
        for(x = 0;x < r; x ++)
        {
            y = sqrt(r * r - x * x) + 0.5;
            set_pixel(sur,ox + x,oy + y,bc);
            set_pixel(sur,ox + x,oy - y,bc);
            set_pixel(sur,ox - x,oy -y,bc);
            set_pixel(sur,ox - x,oy + y,bc);
        }
        for(y = 0;y < r; y ++)
        {
            x = sqrt(r * r - y * y) + 0.5;
            set_pixel(sur,ox + x,oy + y,bc);
            set_pixel(sur,ox + x,oy - y,bc);
            set_pixel(sur,ox - x,oy -y,bc);
            set_pixel(sur,ox - x,oy + y,bc);
        }
    }
}
