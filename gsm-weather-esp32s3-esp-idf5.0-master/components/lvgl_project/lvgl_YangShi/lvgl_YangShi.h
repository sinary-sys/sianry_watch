#ifndef __LVGL_YangShi_H__
#define __LVGL_YangShi_H__

#include "lvgl.h"


#define yangshi_moren_bg LV_COLOR_MAKE(0x00, 0x00, 0x00)

#define rili_biankuang_bg_color LV_COLOR_MAKE(0x00, 0x00, 0x00)
#define rili_bg_color yangshi_moren_bg

typedef struct
{
	char buf[20];
	int image_cnt;



}_lvgl_YangShi_GongNeng_Data;

extern _lvgl_YangShi_GongNeng_Data lvgl_YangShi_GongNeng_Data;

extern lv_style_t lvgl_font12_style;
extern lv_style_t lvgl_font16_style;
extern lv_style_t lvgl_font24_style;
extern lv_style_t lvgl_font_acsii_48_style;
extern lv_style_t lvgl_font_acsii_12_style;
extern lv_style_t lvgl_font_acsii_16_style;

extern lv_style_t lvgl_font_acsii_32_style;
extern lv_style_t lvgl_WuBianKuang_cont_style;
extern lv_style_t lvgl_font_ZiDing_K8_24_style;
extern lv_style_t lvgl_ta_moren_style;		//文本输入默认样式
extern lv_style_t lvgl_touming_cont_style;//透明cont样式

extern lv_style_t lvgl_preload_SPINNING_style;		//preload底部圆形默认样式
extern lv_style_t lvgl_preload_FILLSPIN_style;		//preload旋转的弧形默认样式

extern lv_style_t lvgl_switch_on_style;		//switch的开状态默认样式
extern lv_style_t lvgl_switch_off_style;		//switch的关状态默认样式
extern lv_style_t lvgl_switch_background_style;	//switch的背景默认样式
extern lv_style_t lvgl_switch_knob_style;	//switch的指示器默认样式

extern lv_style_t lvgl_rili_bg_style;				//日历背景默认样式
extern lv_style_t lvgl_rili_header_style;			//日历header默认样式
extern lv_style_t lvgl_rili_day_name_style;			//日历day_name默认样式
extern lv_style_t lvgl_rili_date_style;			//日历data默认样式


extern lv_style_t lvgl_kb_TEXT_LOWER_moren_style;		//键盘背景默认样式
extern lv_style_t lvgl_kb_TEXT_UPPER_moren_style;		//键盘按钮默认样式


void lvgl_YangShi_create(void);
void YangShi_RiLi(void);
void lvgl_kb_yangshi_init(void);
void lvgl_yangshi_preload(void);


#endif
