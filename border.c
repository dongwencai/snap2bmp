#include "surface.h"
#include "rectangle.h"
#include "line.h"
#include "globalColor.h"

#define RGBA888TORGBA656(color) (((((color) >> 19) & 0x1f) << 11) \
                                                |((((color) >> 10) & 0x3f) << 5) \
                                            |(((color) >> 3) & 0x1f))
/*
int window_border(surface_t *sur,rect_t rect)
{
    uint16_t nx,ny;
    coord_t point;
    if(sur->Bpp == 2)
    {
        color1 = RGBA888TORGBA656(0xd4d0c8);
        color2 = RGBA888TORGBA656(0xffffff);
        color3 = RGBA888TORGBA656(0x404040);
        color4 = RGBA888TORGBA656(0x808080);
    }
    nx = rect.p1.x - rect.p0.x + 1;
    ny = rect.p1.y - rect.p0.y + 1; 
    point = rect.p0;
    line_horizontal(sur,point,nx,color1);
    line_vertical(sur,point,ny,color1);
    point.y += 1;
    point.x += 1;
    line_horizontal(sur,point,nx - 2,color2);
    line_vertical(sur,point,ny - 2,color2);
    point.x = rect.p0.x;
    point.y = rect.p1.y;
    line_horizontal(sur,point,nx,color3);
    point.x += 1;
    point.y -= 1;
    line_horizontal(sur,point,nx - 2,color4);
    point.x = rect.p1.x;
    point.y = rect.p0.y;
    line_vertical(sur,point,ny,color3);
    point.x -= 1;
    point.y += 1;
    line_vertical(sur,point,ny - 2,color4);
    return 0;
}

int btn_border(surface_t *sur,rect_t rect,int btn_pressed)
{
    uint16_t nx,ny;
    coord_t point;
    uint32_t color;
    point = rect.p0;
    nx = rect.p1.x - rect.p0.x + 1;
    ny = rect.p1.y - rect.p0.y + 1;
    color = btn_pressed ? color3 : color2;
    line_horizontal(sur,point,nx,color);
    line_vertical(sur,point,ny,color);
    point.x += 1;
    point.y += 1;
    color = btn_pressed ? color4 : color1;
    line_horizontal(sur,point,nx - 2,color);
    line_vertical(sur,point,ny - 2,color);
    point.x = rect.p0.x;
    point.y = rect.p1.y;
    color = btn_pressed ? color2 : color3;
    line_horizontal(sur,point,nx,color);
    point.x += 1;
    point.y -= 1;
    color = btn_pressed ? color1 : color4;
    line_horizontal(sur,point,nx - 2,color);
    point.x = rect.p1.x;
    point.y = rect.p0.y;
    color = btn_pressed ? color2 : color3;
    line_vertical(sur,point,ny,color);
    point.x -= 1;
    point.y += 1;
    color = btn_pressed ? color1 : color4;
    line_vertical(sur,point,ny - 2,color);
}

int text_border(surface_t *sur,rect_t rect,int text_status)
{
    uint16_t nx,ny;
    coord_t point;
    uint32_t color;
    point = rect.p0;
    nx = rect.p1.x - rect.p0.x + 1;
    ny = rect.p1.y - rect.p0.y + 1;
    color = color4;
    line_horizontal(sur,point,nx,color);
    line_vertical(sur,point,ny,color);
    point.x += 1;
    point.y += 1;
    color = color3;
    line_horizontal(sur,point,nx - 2,color);
    line_vertical(sur,point,ny - 2,color);
    point.x = rect.p0.x;
    point.y = rect.p1.y;
    color = color2;
    line_horizontal(sur,point,nx,color);
    point.x += 1;
    point.y -= 1;
    color = color1;
    line_horizontal(sur,point,nx - 2,color);
    point.x = rect.p1.x;
    point.y = rect.p0.y;
    color = color2;
    line_vertical(sur,point,ny,color);
    point.x -= 1;
    point.y += 1;
    color = color1;
    line_vertical(sur,point,ny - 2,color);
}*/
