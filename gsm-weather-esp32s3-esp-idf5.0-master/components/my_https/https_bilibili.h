#ifndef __https_bilibili__
#define __https_bilibili__

#include "stdio.h"
#include "stdint.h"

#if 1
  #define https_bilibili_DEBUG(format, ...)  my_debug("[https哔哩哔哩]- ",format,##__VA_ARGS__);
#else
  #define https_bilibili_DEBUG(format, ...)  ;
#endif

#define HTTPS_BILIBILI_ID "430380301"
#define HTTPS_bilibili_fensi  "https://api.bilibili.com/x/relation/stat?jsonp=jsonp&vmid="

#define HTTPS_bilibili_bofang "https://api.bilibili.com/x/space/upstat?mid="

typedef struct
{
  char id[20];
	char fensi[20];         //粉丝
	char bofang[20];        //播放
  char guanzhu[20];       //关注
  char wenzhang[20];       //文章播放量


}_bilibili_Data;

int https_get_bilibili_fensi(void);
int https_get_bilibili_bofang(void);
int HTTP_Get_bilibili(char * id,_bilibili_Data  *read_buf);
int HTTP_Get_bilibili_bofang(char * id,_bilibili_Data  *read_buf);
#endif
