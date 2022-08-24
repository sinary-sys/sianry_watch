#ifndef __LVGL_desktop_H__
#define __LVGL_desktop_H__

#include "lvgl.h"
#include "lvgl_Project.h"

#if 1
#define desktop_DEBUG(format, ...) lvgl_project_debug("[桌面]-",format,##__VA_ARGS__);
#else
#define desktop_DEBUG(format, ...) ;
#endif

#define desktop_Button_Num 13

#define desktop_event_anXia 100


typedef struct
{
	lv_obj_t *lvgl_TianQi;
	lv_obj_t *lvgl_BZhan;
	lv_obj_t *lvgl_HuangLi;
	lv_obj_t *lvgl_SheZhi;
	lv_obj_t *lvgl_RiLi;
	lv_obj_t *lvgl_YouXi;
	lv_obj_t *lvgl_YinYue;
	lv_obj_t *lvgl_ShiPin;
	lv_obj_t *lvgl_JiSuanQi;
	lv_obj_t *lvgl_NaoZhong;

	lv_obj_t *lvgl_btn_DongHua;
	lv_style_t lvgl_btn_DongHua_style;
	lv_anim_t lv_DongHua_anim;
	lv_area_t lv_DongHua_area;

	lv_anim_t lv_anim_Jin[desktop_Button_Num];
	lv_anim_t lv_anim_Chu[desktop_Button_Num];


}_desktop_ChuangKou;

extern _desktop_ChuangKou desktop_ChuangKou;
typedef struct
{
	char buf[20];
	int image_cnt;

	int DongHua_KaiShiZhi;//动画开始时初始值
	int DongHua_Flag;//进入应用时动画是否结束标志位
	int AnXia_Num;//按下的按钮

	lv_obj_t *AnXia_button;
	lv_point_t point;
}_lvgl_desktop_GongNeng_Data;

extern _lvgl_desktop_GongNeng_Data lvgl_desktop_GongNeng_Data;


void lvgl_desktop_create(lv_obj_t * Fu);
void lvgl_desktop_close(void);
void lvgl_desktop_hidden(void);
void lvgl_desktop_TaskCb(lv_task_t *t);
void desktop_DongHua_Jin(void);
void desktop_DongHua_Chu(void);

#endif
