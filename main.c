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

#define RGBA888TORGBA656(color) ((((color) >> 19) & 0x1f) << 11) \
                                                |((((color) >> 10) & 0x3f) << 5) \
                                            |(((color) >> 3) & 0x1f) 
typedef struct
{
    char rgbBlue;
    char rgbGreen;
    char rgbRed;
    char rgbReserved;
} RGBQUAD;

BITMAPFILEHEADER FileHead;
BITMAPINFOHEADER InfoHead;
RGBQUAD rgbquad;

char *fbp = 0;
int xres = 0;
int yres = 0;
int bits_per_pixel = 0;
int tty;
int tty_mode_was;


int set_tty_graphics( void );
int set_tty_text( void );
int  show_bmp  ( char *bmpfile );
long chartolong( char * string, int length );
/******************************************************************************
 *
 ******************************************************************************/
int main( int argc, char *argv[] )
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (!fbfd)
    {
        printf("Error: cannot open framebuffer device.\n");
        exit(1);
    }

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo))
    {
        printf("Error reading fixed information.\n");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo))
    {
        printf("Error reading variable information.\n");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel );
    
    xres = vinfo.xres;
    yres = vinfo.yres;
    bits_per_pixel = vinfo.bits_per_pixel;

   
    //xres += 10;
    printf("xres:%d\n",xres);
    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
            fbfd, 0);
    if ((int)fbp == -1)
    {
        printf("Error: failed to map framebuffer device to memory.\n");
        exit(4);
    }

    if (/*set_tty_graphics()*/1)
    {
        show_bmp( argv[1] );
    }
    //sleep( 10 );
    //set_tty_text();

    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}
/******************************************************************************
 *
 ******************************************************************************/
int show_bmp( char *bmpfile )
{
    FILE *fp;
    char *tmp = NULL;
    int rc;
    int color;
    int ciBitCount, ciWidth, ciHeight;
    int line_x, line_y;
    long int location = 0, BytesPerLine = 0,pos = 0;
    bmp_info_t *binfo = NULL;
    binfo = load_bmp(bmpfile);
    bmp_left_rotate(binfo,LEFT_ROTATE);
    if(binfo)
    {
        int i,j;
        tmp = (char *)malloc(binfo->stride / 2 );
        for(line_y = 0;line_y < binfo->height;line_y ++)
        {
            for(i = 0,j = 0;i < binfo->stride ; i += 4,j += 2)
            {
                /*
                color = 0;
                color = (binfo->buf[i] << 16);
                color |= (binfo->buf[i + 1] << 8);
                color |= binfo->buf[i + 2];
                */
                *(short *)&tmp[j] = (short)RGBA888TORGBA656(*(unsigned int *)&binfo->buf[i]);
            }
            pos = line_y * xres * bits_per_pixel / 8; 
            //memcpy(fbp + pos,tmp,binfo->stride / 2 );
            memcpy(fbp + pos,&binfo->buf[line_y * binfo->stride],binfo->stride );
        }
        free(tmp);
    }
}
int set_tty_graphics( void )
{
    int ret = 1;

    if(0 > (tty = open("/dev/tty0", O_RDWR)))
    {
        printf( "ERROR: /dev/tty0 open failed\n" );
        ret = 0;
    }
    else if(0 > ioctl(tty, KDGETMODE, &tty_mode_was))
    {
        printf( "ERROR: /dev/tty0 get mode failed\n");
        close(tty);
        ret = 0;
    }
    else if((KD_GRAPHICS != tty_mode_was)
            && (0 > ioctl(tty, KDSETMODE, KD_GRAPHICS)))
    {
        printf( "ERROR: /dev/tty0 set graphics failed\n");
        close(tty);
        ret = 0;
    }
    else
    {
        printf("tty mode was ");
        switch(tty_mode_was)
        {
            case KD_TEXT     :  printf("KD_TEXT"     ); break;
            case KD_GRAPHICS :  printf("KD_GRAPHICS" ); break;
            default          :  printf("IMPOSSIBLE!" ); break;
        }
        printf("\n");
        printf("tty mode set to KD_GRAPHICS\n");
        fflush(stdout);
        close(tty);
    }
    return( ret );
}

/******************************************************************************
 *
 ******************************************************************************/
int set_tty_text( void )
{
    int ret = 1;

    if(0 > (tty = open("/dev/tty0", O_RDWR)))
    {
        printf( "ERROR: /dev/tty0 open failed\n" );
        ret = 0;
    }
    else if(0 > ioctl(tty, KDSETMODE, tty_mode_was))
    {
        printf( "ERROR: /dev/tty0 reset mode failed\n");
        close(tty);
        ret = 0;
    }
    else
    {
        printf("tty mode set to ");
        switch(tty_mode_was)
        {
            case KD_TEXT     :  printf("KD_TEXT"     ); break;
            case KD_GRAPHICS :  printf("KD_GRAPHICS" ); break;
            default          :  printf("IMPOSSIBLE!" ); break;
        }
        printf("\n");
        fflush(stdout);
        close(tty);
    }
    return( ret );
}

