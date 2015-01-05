#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include "bmp.h"
#include "surface.h"
#include "line.h"
#include "arc.h"
#include "rectangle.h"
#include "border.h"
#include "button.h"
#include "text.h"

#define RGBA888TORGBA656(color) (((((color) >> 19) & 0x1f) << 11) \
                                                |((((color) >> 10) & 0x3f) << 5) \
                                            |(((color) >> 3) & 0x1f))
int  show_bmp  ( char *bmpfile,surface_t *sur );

extern int openfb(char *devname,surface_t *sur);
int main( int argc, char *argv[] )
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    surface_t sur;
    long int screensize = 0;
    openfb("/dev/fb0",&sur); 
    if (argc > 1)
    {
        show_bmp( argv[1],&sur);
    }
    return 0;
}
/******************************************************************************
 *
 ******************************************************************************/
int show_bmp( char *bmpfile,surface_t *sur)
{
    FILE *fp;
    char *tmp = NULL;
    unsigned int color,a,r,g,b,color1,color2,color3,color4,b1 = 0xD4D0C8,b2;
    int  line_y;
    long int pos = 0;
    bmp_info_t *binfo = NULL;
    coord_t x = {100,100};
    coord_t x0 = {100,200};
    coord_t x1 = {100,400};
    coord_t x2 = {400,200};
    coord_t x3 = {100,200};
    coord_t x4 = {0,0};
    coord_t x5 = {200,300};
    coord_t x6 = {0,0};
    coord_t x7 = {200,50};
    coord_t x8 = {0,0};
    coord_t x9 = {200,200};
    coord_t x10 = {300,250};
    coord_t x11 ={200,400};
    rect_t rect = {x,x2};
    binfo = load_bmp(bmpfile);
    //bmp_rotate(binfo,LEFT_ROTATE);
    if(binfo && 0)
    {
        int i,j;
        tmp = (char *)malloc(binfo->stride / 2 );
        for(line_y = 0;line_y < binfo->height;line_y ++)
        {
            for(i = 0,j = 0;i < binfo->stride ; i += 4,j += 2)
            {
                color = 0;
                a = binfo->buf[i];
                r = binfo->buf[i + 1] << 8;
                g = binfo->buf[i + 2] << 16;
                b = binfo->buf[i + 3] << 24;
                color = a | r | g | b;
                color = *(unsigned int *)&binfo->buf[i];
                *(short *)&tmp[j] = (short)RGBA888TORGBA656(color);
            }
            pos = line_y * sur->stride; 
            memcpy(sur->buf + pos,tmp,binfo->stride / 2 );
            //memcpy(sur->buf + pos,&binfo->buf[line_y * binfo->stride],binfo->stride );
        }
        free(tmp);
    }
    color = 0x1f << 11;
    /*
    color1 = RGBA888TORGBA656(b1);
    color2 = RGBA888TORGBA656(0xffffff);
    color3 = RGBA888TORGBA656(0x404040);
    color4 = RGBA888TORGBA656(0x808080);
    */
    color1 =(b1);
    color2 =(0xffffff);
    color3 =(0x404040);
    color4 =(0x808080);
    /*
    line_horizontal(sur,x,200,color); 
    line_vertical(sur,x,200,color);
    line(sur,x0,x1,color);
    line(sur,x2,x3,color);
    line(sur,x4,x5,color);
    line(sur,x6,x7,color);
    line(sur,x8,x9,color);
    */
    arc(sur,30,120,x9.x,x9.y,100,color,color2);    
    arc(sur,180,290,x9.x,x9.y,100,color,color1);    
    //circle(sur,x9.x,x9.y,100,color,color1);
    //window_border(sur,rect);
    while(0)
    {
        //ctrl_text(sur,rect,1); 
        ctrl_button(sur,rect,1);
        sleep(1);
        ctrl_button(sur,rect,0);
        sleep(1);
    }
    //line(sur,x10,x9,color);
}

