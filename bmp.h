#ifndef __BMP_H__
#define __BMP_H__
#include <stdint.h>
typedef struct
{  
    uint16_t bfType;    
    int32_t bfSize; 
    uint16_t bfReserved1; 
    uint16_t bfReserved2; 
    int32_t bfOffBits; 
}__attribute__((packed)) BITMAPFILEHEADER; 

typedef struct
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

typedef struct{
    int height;
    int width;
    short bpp;
    uint16_t stride;
    uint8_t buf[0];
}bmp_info_t;

typedef enum{
    FILE_NOT_EXIST,
    FILE_BROKEN,
    FORMAL_NOT_SUPPORT,
}bmp_err_e;

typedef enum{
    LEFT_ROTATE,
    RIGHT_ROTATE,
}bmp_rotate_e;

typedef enum{
   MALLOC_FAIL, 
}common_err_e;

bmp_info_t *load_bmp(char *file);

int bmp_left_rotate(bmp_info_t *pbmpinfo,bmp_rotate_e direction);


#endif

