#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <linux/fb.h>
#include <linux/kd.h>/*新添加的，用于进行图形模式时ioctl使用*/
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include "bmp.h"
#include "surface.h"
#include "line.h"

#define RGBA888TORGBA656(color) ((((color) >> 19) & 0x1f) << 11) \
                                                |((((color) >> 10) & 0x3f) << 5) \
                                            |(((color) >> 3) & 0x1f) 
int  show_bmp  ( char *bmpfile,surface_t sur );

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
        show_bmp( argv[1],sur);
    }
    return 0;
}
/******************************************************************************
 *
 ******************************************************************************/
int show_bmp( char *bmpfile,surface_t sur)
{
    FILE *fp;
    char *tmp = NULL;
    int rc;
    unsigned int color,a,r,g,b;
    int line_x, line_y;
    long int pos = 0;
    bmp_info_t *binfo = NULL;
    binfo = load_bmp(bmpfile);
    coord_t x = {100,100};
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
                //color = *(unsigned int *)&binfo->buf[i];
                *(short *)&tmp[j] = (short)RGBA888TORGBA656(color);
            }
            pos = line_y * sur.stride; 
            memcpy(sur.buf + pos,tmp,binfo->stride / 2 );
            memcpy(sur.buf + pos,&binfo->buf[line_y * binfo->stride],binfo->stride );
        }
        free(tmp);
    }
    color = 0x1f << 11;
    line_horizontal(&sur,x,200,color); 
    line_vertical(&sur,x,200,color);
}

