#include "bmp.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bmp_info_t *load_bmp(char *file)
{
   FILE *fp = NULL;
   char *tmp = NULL;
   bmp_info_t *pbi = NULL;
   int status = FILE_NOT_EXIST,len = 0,context_len,i,j;
   BITMAPINFOHEADER bmpinfo;
   BITMAPFILEHEADER bmpfile;
   fp = fopen(file,"rb");
   if(!fp)  goto err;
   len = fread(&bmpfile,1,sizeof(BITMAPFILEHEADER),fp); 
   len += fread(&bmpinfo,1,sizeof(BITMAPINFOHEADER),fp); 
   if(len < 54) goto err;
   context_len = bmpinfo.biBitCount * bmpinfo.biWidth * bmpinfo.biHeight / 8;
   pbi = malloc(context_len + sizeof(bmp_info_t));
   tmp = malloc(context_len);
   if(!pbi || !tmp)     goto err;
   pbi->bpp = bmpinfo.biBitCount;
   pbi->height = bmpinfo.biHeight;
   pbi->width = bmpinfo.biWidth;
   pbi->stride = bmpinfo.biWidth * bmpinfo.biBitCount / 8;
   if (memcmp(&bmpfile.bfType, "BM", 2) != 0)    goto err;
   len += fread(tmp,1,context_len,fp);
   if(len < context_len + 54)   goto err;
   for(i = pbi->height - 1,j = 0;i >= 0; i --,j ++)
   {
       memcpy(&(pbi->buf[j * pbi->stride]),&tmp[i * pbi->stride],pbi->stride);
   }
   free(tmp);
   fclose(fp);
   return pbi;
err:
   if(fp)
       fclose(fp);
   if(tmp)
       free(tmp);
   if(pbi)
       free(pbi);
   return NULL;
}
int bmp_rotate(bmp_info_t *pbmpinfo,bmp_rotate_e direction)
{
    bmp_info_t *tmp = NULL;
    int i,j;
    if(!pbmpinfo) return -1;
    tmp = (bmp_info_t *)malloc(pbmpinfo->stride * pbmpinfo->height + sizeof(bmp_info_t));
    *tmp = *pbmpinfo;
    SWAP(tmp->height,tmp->width);
    tmp->stride = tmp->width * tmp->bpp / 8;
    if(direction == LEFT_ROTATE)
    {
        for(i = 0;i < pbmpinfo->height;i ++) 
            for(j = 0;j < pbmpinfo->width;j ++)
                    memcpy(&tmp->buf[(tmp->height - j - 1) * tmp->stride + i * tmp->bpp / 8],&pbmpinfo->buf[i * pbmpinfo->stride + j * pbmpinfo->bpp / 8 ],tmp->bpp / 8);
    }
    else
    {
        for(i = 0;i < pbmpinfo->height;i ++) 
            for(j = 0;j < pbmpinfo->width;j ++)
                    memcpy(&tmp->buf[j * tmp->stride + (tmp->width - i -1) * tmp->bpp / 8],&pbmpinfo->buf[i * pbmpinfo->stride + j * pbmpinfo->bpp / 8 ],tmp->bpp / 8);
    }
    memcpy(pbmpinfo,tmp,sizeof(bmp_info_t) + tmp->height * tmp->stride);
    free(tmp);
}

