#include "surface.h"
#include "rectangle.h"
#include "globalColor.h"
#include "line.h"
#include "border.h"

int ctrl_button(surface_t *sur,rect_t rect,int btn_pressed)
{
    rect_t fill ;
//    btn_border(sur,rect,btn_pressed);
    fill.p0.x = rect.p0.x + 2;
    fill.p0.y = rect.p0.y + 2;
    fill.p1.x = rect.p1.x - 2;
    fill.p1.y = rect.p1.y - 2;
//    rectangle(sur,fill,0x0,color1);
}
