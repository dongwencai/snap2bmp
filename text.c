#include "surface.h"
#include "rectangle.h"
#include "border.h"
#include "globalColor.h"

int ctrl_text(surface_t *sur,rect_t rect,int text_status)
{
    rect_t fill ;
//    text_border(sur,rect,text_status);     
    fill.p0.x = rect.p0.x + 2;
    fill.p0.y = rect.p0.y + 2;
    fill.p1.x = rect.p1.x - 2;
    fill.p1.y = rect.p1.y - 2;
//    rectangle(sur,fill,0x0,color2);
}
