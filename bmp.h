#ifndef __BMP_H__
#define __BMP_H__

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
    uint32_t buf[0];
    uint16_t stride;
}bmp_info_t;

typedef enum{
    FILE_NOT_EXIST,
    FILE_BROKEN,
    FORMAL_NOT_SUPPORT;
}bmp_err_e;
typedef enum{
   MALLOC_FAIL, 
}common_err_e;
#endif

