#ifndef __LVGL_RiLi_H__
#define __LVGL_RiLi_H__

#include "lvgl.h"
#include "lvgl_Project.h"
#include "my_system.h"

#if 1
#define RiLi_DEBUG(format, ...) lvgl_project_debug("[日历]- ",format,##__VA_ARGS__);
#else
#define RiLi_DEBUG(format, ...) ;
#endif

#define lvgl_RiLi_x 0
#define lvgl_RiLi_y 0
#define lvgl_RiLi_xsize 240
#define lvgl_RiLi_ysize 240

typedef struct
{

	lv_obj_t * calendar;

	lv_task_t * lvgl_task;

	lv_style_t *btn_XuanZhong_style;
	lv_obj_t *btn_XuanZhong;

	lv_anim_t lv_anim_jin;
	lv_anim_t lv_anim_chu;

}_lvgl_RiLi_ChuangKou;

extern _lvgl_RiLi_ChuangKou lvgl_RiLi_ChuangKou;
typedef struct
{
	char buf[20];


	int AnXia_Num;//按下的按钮编号
	lv_obj_t *AnXia_button;//按下的按钮句柄

	int DongHua_Flag;

	lv_point_t point;


}_lvgl_RiLi_GongNeng_Data;

extern _lvgl_RiLi_GongNeng_Data lvgl_RiLi_GongNeng_Data;

extern lv_obj_t *lvgl_RiLi_main_cont;

void lvgl_RiLi_create(lv_obj_t * Fu);
void lvgl_RiLi_close(void);
void lvgl_RiLi_closed(void);
void lvgl_RiLi_TaskCb(lv_task_t *t);


#endif
