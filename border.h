#ifndef __BORDER_H__
#define __BORDER_H__
#include "surface.h"
#include "rectangle.h"
extern int window_border(surface_t *sur,rect_t rect);

extern int btn_border(surface_t *sur,rect_t rect,int btn_pressed);
extern int text_border(surface_t *sur,rect_t rect,int text_status);
#endif
