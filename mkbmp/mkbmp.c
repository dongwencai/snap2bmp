#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
static char flag_o,flag_i,option_bpp,xres,yres;
static int32_t width = 1376,height = 768,bpp = 32;
//static int32_t width = 100,height = 100,bpp = 32;

typedef struct tagBITMAPFILEHEADER 
{  
    uint16_t bfType;    
    int32_t bfSize; 
    uint16_t bfReserved1; 
    uint16_t bfReserved2; 
    int32_t bfOffBits; 
}__attribute__((packed)) BITMAPFILEHEADER; 
typedef struct tagBITMAPINFOHEADER 
{ 
    int32_t biSize; 
    int32_t biWidth; 
    int32_t biHeight; 
    int16_t biPlanes; 
    int16_t biBitCount; 
    int32_t biCompression; 
    int32_t biSizeImage; 
    int32_t biXPelsPerMeter; 
    int32_t biYPelsPerMeter; 
    int32_t biClrUsed; 
    int32_t biClrImportant; 
}__attribute__((packed)) BITMAPINFOHEADER;
int main(int argc,char *argv[])
{
    BITMAPFILEHEADER bmpfileheader = {0};
    BITMAPINFOHEADER bmpinfoheader = {0};
    int bytes_per_line ,i;
    char *buffer = NULL;
    bmpfileheader.bfType = 0x4d42;
    bmpfileheader.bfOffBits = 0x36;
    bmpinfoheader.biSize = 0x28;
    bmpinfoheader.biPlanes = 0x1;
    bmpinfoheader.biCompression = 0x0;

    bmpinfoheader.biWidth = width;
    bmpinfoheader.biHeight = height;
    bmpinfoheader.biBitCount = bpp;
    bmpfileheader.bfSize = width * height * bpp / 8 + 56;
    bmpinfoheader.biSize = 0x28;
    bmpinfoheader.biXPelsPerMeter = bmpinfoheader.biYPelsPerMeter = 0x2e20;
    bytes_per_line = width * bpp / 8;
    buffer =(char *) malloc(bytes_per_line * height);
    if(argc > 5 && buffer)
    {
        width = atoi(argv[3]);
        height = atoi(argv[4]);
        bpp = atoi(argv[5]);
        FILE *fpSrc = NULL,*fpDst = NULL;
        int line;
        fpSrc = fopen (argv[1],"rb");
        fpDst = fopen (argv[2],"w+");
        fwrite(&bmpfileheader,1,sizeof(bmpfileheader),fpDst);
        fwrite(&bmpinfoheader,1,sizeof(bmpinfoheader),fpDst);
        fread(buffer,bytes_per_line,height,fpSrc);
        for(line = height -1;line >= 0;line --)
            fwrite(&buffer[line * bytes_per_line],1,bytes_per_line,fpDst);
        buffer[0] = buffer[1] = '\0';
        fwrite(buffer,1,2,fpDst);
        free(buffer);
        fclose(fpSrc);
        fclose(fpDst);
    }
}
