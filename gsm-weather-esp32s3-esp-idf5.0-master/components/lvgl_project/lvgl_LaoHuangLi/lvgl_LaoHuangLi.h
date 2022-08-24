#ifndef __LVGL_LaoHuangLi_H__
#define __LVGL_LaoHuangLi_H__

#include "lvgl_Project.h"


#if 1
#define LaoHuangLi_DEBUG(format, ...) lvgl_project_debug("[老黄历]- ",format,##__VA_ARGS__);
#else
#define LaoHuangLi_DEBUG(format, ...) ;
#endif

enum {
	lvgl_LaoHuangLi_ShuaXin_JieShu=0,
	lvgl_LaoHuangLi_ShuaXin_KaiShi,
	lvgl_LaoHuangLi_ShuaXin_Zhong,


}lvgl_LaoHuangLi_ShuaXin_Sta;

typedef struct
{
	int ShuaXin_Sta;
	int DongHua_Sta;


	lv_anim_t lv_anim_WuXing;
	lv_anim_t lv_anim_ChongSha;
	lv_anim_t lv_anim_Yi;
	lv_anim_t lv_anim_Ji;
	lv_anim_t lv_anim_JiShenYiQu;
	lv_anim_t lv_anim_XiongShenYiJi;



}_lvgl_LaoHuangLi_GongNeng_Data;

extern _lvgl_LaoHuangLi_GongNeng_Data lvgl_LaoHuangLi_GongNeng_Data;


void lvgl_LaoHuangLi_create(lv_obj_t * Fu);
void lvgl_LaoHuangLi_close(void);
void lvgl_LaoHuangLi_TaskCb(lv_task_t *t);



void lvgl_LaoHuangLi_anim_WuXing_cb(void * arc, lv_anim_value_t v);
void lvgl_LaoHuangLi_anim_ChongSha_cb(void * arc, lv_anim_value_t v);
void lvgl_LaoHuangLi_anim_Yi_cb(void * arc, lv_anim_value_t v);
void lvgl_LaoHuangLi_anim_Ji_cb(void * arc, lv_anim_value_t v);
void lvgl_LaoHuangLi_anim_JiShenYiQu_cb(void * arc, lv_anim_value_t v);
void lvgl_LaoHuangLi_anim_XiongShenYiJi_cb(void * arc, lv_anim_value_t v);

void lvgl_LaoHuangLi_ShuaXin_kaishi(void);
void lvgl_LaoHuangLi_ShuaXin_jieshu(void);
void lvgl_LaoHuangLi_DongHua_Jin(void);
void lvgl_LaoHuangLi_DongHua_Chu(void);

void lvgl_LaoHuangLi_Set_WuXing(char *str);
void lvgl_LaoHuangLi_Set_ChongSha(char *str);
void lvgl_LaoHuangLi_Set_Yi(char *str);
void lvgl_LaoHuangLi_Set_Ji(char *str);
void lvgl_LaoHuangLi_Set_JiShenYiQu(char *str);
void lvgl_LaoHuangLi_Set_XiongShenYiJi(char *str);
void lvgl_LaoHuangLi_Set_YinLi(char *str);
void lvgl_LaoHuangLi_Set_YangLi(char *str);

#endif
