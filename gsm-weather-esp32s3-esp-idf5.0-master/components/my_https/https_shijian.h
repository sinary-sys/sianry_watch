#ifndef __https_shijiani__
#define __https_shijiani__

#include "stdio.h"
#include "stdint.h"

#if 1
  #define shijiani_DEBUG(format, ...)  my_debug("[http时间]- ",format,##__VA_ARGS__);
#else
  #define shijiani_DEBUG(format, ...)  ;
#endif


//苏宁时间校准
#define HTTPS_SuNing_ShiJian    "http://quan.suning.com/getSysTime.do"

typedef struct
{
  char riqi[20];
  char shijian[20];
	int nian;
  int yue;
  int ri;
  int shi;
  int fen;
  int miao;
  int xingqi;

}_RiQi_Data;

int https_get_ShiJian(void);
int HTTP_Get_ShiJian(_RiQi_Data * read_buf);

#endif
