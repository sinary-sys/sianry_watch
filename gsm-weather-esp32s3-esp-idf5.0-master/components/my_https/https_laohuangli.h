#ifndef __https_laohuangli__
#define __https_laohuangli__

#include "stdio.h"
#include "stdint.h"

#if 1
  #define laohuangli_DEBUG(format, ...)  my_debug("[https老黄历]- ",format,##__VA_ARGS__);
#else
  #define laohuangli_DEBUG(format, ...)  ;
#endif


//聚合数据 老黄历 https://www.juhe.cn/box/index/id/65
#define HTTPS_laohuangli_key "a5d96310d1119465e6a5017c28d866c5"

#define HTTPS_laohuangli "http://v.juhe.cn/laohuangli/d?key="HTTPS_laohuangli_key"&date="

typedef struct
{

    char reason[20]; //返回说明
    char id[20];//id
    char yangli[20];//阳历
    char yinli[100];//阴历
    char wuxing[200];//五行
    char chongsha[200];//冲煞
    char baiji[200];//彭祖百忌
    char jishen[200];//吉神宜趋
    char yi[200];//宜
    char xiongshen[200];//凶神宜忌
    char ji[200];//忌


}_laohuangli_data;

int https_get_LaoHuangLi(char * riqi,_laohuangli_data  *read_buf);

#endif
