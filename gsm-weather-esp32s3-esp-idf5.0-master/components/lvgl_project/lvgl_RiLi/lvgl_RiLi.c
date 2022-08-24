#include "lvgl_RiLi.h"
#include "lvgl_Project.h"
//#include "lvgl_SheZhi.h"
#include "lvgl_RiLi_anim.h"


_lvgl_RiLi_GongNeng_Data lvgl_RiLi_GongNeng_Data;
_lvgl_RiLi_ChuangKou lvgl_RiLi_ChuangKou;

lv_obj_t *lvgl_RiLi_main_cont = NULL;
lv_style_t lvgl_RiLi_style;


//周日,周一,周二,....,周六
const char * const day_names[7] = { "周日","周一","周二","周三","周四","周五","周六" };

//一月,二月,三月...,十二月
//const char * const month_names[12] = { "一月","二月","三月","四月","五月","六月","七月","八月","九月","十月","十一月","十二月" };
//一月,二月,三月...,十二月
const char * const month_names[12] = { "-01","-02","-03","-04","-05","-06","-07","-08","-09","-10","-11","-12" };



const char*RiLi_TEXT[][SYSTEM_LANGUAGE_NUM] =
{
	{ "日历", "日历", "Calendar", NULL},



};




void lvgl_RiLi_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	if (obj == lvgl_RiLi_main_cont)
	{
		//RiLi_DEBUG("cb:%d\r\n", event);
		switch (event)
		{

		case LV_EVENT_DELETE:

			lvgl_RiLi_closed();
			break;

		case LV_EVENT_PRESSING://对象被持续按下


			break;
		case LV_EVENT_PRESSED://对象已被按下


			break;
		case LV_EVENT_DRAG_END://拖动结束后


			if (lv_obj_get_y(lvgl_RiLi_main_cont) != 0)
			{

				lv_obj_set_y(lvgl_RiLi_main_cont, 0);
			}

			if (lv_obj_get_x(lvgl_RiLi_main_cont) != 0)
			{
				if (lv_obj_get_x(lvgl_RiLi_main_cont) > 100)
				{


					lvgl_RiLi_close();


				}
				else
				{
					lv_obj_set_x(lvgl_RiLi_main_cont, 0);
				}
			}
			break;
			break;

		case LV_EVENT_RELEASED://按钮释放

		case LV_EVENT_LONG_PRESSED://按钮长按

			break;

		default:
			break;

		}

	}
}


void lvgl_RiLi_create(lv_obj_t * Fu)
{

	if (lvgl_RiLi_main_cont == NULL)
	{

		lv_style_init(&lvgl_RiLi_style);
		lv_style_copy(&lvgl_RiLi_style, &lvgl_WuBianKuang_cont_style);
		/*渐变色*/
		lv_style_set_bg_opa(&lvgl_RiLi_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
		//lv_style_set_bg_color(&lvgl_RiLi_style, LV_STATE_DEFAULT, lv_color_hex(0x1b1d5c));//背景上面颜色
		//lv_style_set_bg_grad_color(&lvgl_RiLi_style, LV_STATE_DEFAULT, lv_color_hex(0x5c418d));//背景上面颜色
		lv_style_set_bg_color(&lvgl_RiLi_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_RiLi_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_dir(&lvgl_RiLi_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);//渐变方向

		/*调整渐变色位置*/
		lv_style_set_bg_main_stop(&lvgl_RiLi_style, LV_STATE_DEFAULT, 10);
		lv_style_set_bg_main_stop(&lvgl_RiLi_style, LV_STATE_DEFAULT, 100);

		//----创建容器----//
		lvgl_RiLi_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_RiLi_main_cont, 0, 0);
		lv_obj_set_size(lvgl_RiLi_main_cont, lv_obj_get_width(Fu), lv_obj_get_height(Fu));
		//lv_obj_set_drag_parent(lvgl_RiLi_main_cont, true); //启用 / 禁用父对象可拖动

		lv_obj_set_click(lvgl_RiLi_main_cont, true); //启用 / 禁用可点击
		lv_obj_set_drag(lvgl_RiLi_main_cont, true);//启用/禁用对象可拖动
		lv_obj_set_drag_dir(lvgl_RiLi_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
		lv_obj_set_drag_throw(lvgl_RiLi_main_cont, false);//启用/禁用拖动后是否有惯性移动

		//lv_obj_set_drag_parent(lvgl_RiLi_main_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_RiLi_main_cont, LV_OBJ_PART_MAIN, &lvgl_RiLi_style);//设置样式
		lv_obj_set_event_cb(lvgl_RiLi_main_cont, lvgl_RiLi_event_cb);//设置回调函数


		lvgl_RiLi_ChuangKou.calendar = lv_calendar_create(lvgl_RiLi_main_cont, NULL);//创建日历对象
		lv_obj_set_pos(lvgl_RiLi_ChuangKou.calendar,0,0);
		lv_obj_set_size(lvgl_RiLi_ChuangKou.calendar,  lv_obj_get_width(lvgl_RiLi_main_cont), lv_obj_get_height(lvgl_RiLi_main_cont));
		//lv_obj_align(lvgl_RiLi_ChuangKou.calendar, NULL, LV_ALIGN_CENTER, 0, 0);//设置与屏幕居中对齐
		lv_obj_set_drag_parent(lvgl_RiLi_ChuangKou.calendar, true); //启用 / 禁用父对象可拖动


		lv_obj_add_style(lvgl_RiLi_ChuangKou.calendar, LV_CALENDAR_PART_BG, &lvgl_rili_bg_style);//日历背景样式
		lv_obj_add_style(lvgl_RiLi_ChuangKou.calendar, LV_CALENDAR_PART_HEADER, &lvgl_rili_header_style);//日历header样式
		lv_obj_add_style(lvgl_RiLi_ChuangKou.calendar, LV_CALENDAR_PART_DAY_NAMES, &lvgl_rili_day_name_style);//日历DAY_NAMES样式
		lv_obj_add_style(lvgl_RiLi_ChuangKou.calendar, LV_CALENDAR_PART_DATE, &lvgl_rili_date_style);//日历DAY_NAMES样式

		lv_calendar_set_day_names(lvgl_RiLi_ChuangKou.calendar, (const char **)day_names);//设置星期信息行的标题,也可以不设置,那么lv_calendar会有一个默认的值
		lv_calendar_set_month_names(lvgl_RiLi_ChuangKou.calendar, (const char **)month_names);//设置月份的标题,也可以不设置,那么lv_calendar会有一个默认的值





		lvgl_RiLi_ChuangKou.lvgl_task = lvgl_task_create(lvgl_RiLi_TaskCb, 100, LV_TASK_PRIO_LOWEST, NULL);

		RiLi_DEBUG("创建窗口\r\n");
	}
	else
	{

		RiLi_DEBUG("显示窗口\r\n");
	}
	lv_obj_move_background(lvgl_RiLi_main_cont);

	lv_calendar_date_t today = { 2021,1,5 };//可以定义为局部的

	today.year = system_data.RiQi_Data.nian;
	today.month= system_data.RiQi_Data.yue;
	today.day = system_data.RiQi_Data.ri;

	lv_calendar_set_today_date(lvgl_RiLi_ChuangKou.calendar, &today);//设置 TODAY日期
	lv_calendar_set_showed_date(lvgl_RiLi_ChuangKou.calendar, &today);//跳转到 TODAY日期所在的界面


	lv_obj_set_drag_throw(lvgl_RiLi_main_cont, false);//启用/禁用拖动后是否有惯性移动
	lv_obj_set_pos(lvgl_RiLi_main_cont, 0, 240);
	lvgl_set_obj_show(lvgl_RiLi_main_cont);


	lvgl_RiLi_anim_Jin();

}


void lvgl_RiLi_TaskCb(lv_task_t *t)
{
	static int time=0;

	if (lv_obj_get_y(lvgl_RiLi_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_RiLi_main_cont, true);//启用/禁用拖动后是否有惯性移动

	}

	if (lv_obj_get_x(lvgl_RiLi_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_RiLi_main_cont, false);//启用/禁用拖动后是否有惯性移动
	}

}



void lvgl_RiLi_close(void)
{


	lvgl_desktop_create(lv_scr_act());

	lvgl_task_delete(lvgl_RiLi_ChuangKou.lvgl_task);

	lvgl_RiLi_GongNeng_Data.point.y = lv_obj_get_y(lvgl_RiLi_main_cont);
	lvgl_RiLi_GongNeng_Data.point.x = lv_obj_get_x(lvgl_RiLi_main_cont);

	lv_obj_clean(lvgl_RiLi_main_cont);

	//uint16_t count = lv_obj_count_children(lvgl_RiLi_main_cont);
	//printf("count:%d\r\n", count);

	lv_obj_del(lvgl_RiLi_main_cont);
}


void lvgl_RiLi_closed(void)
{
	RiLi_DEBUG("删除窗口\r\n");
	RiLi_DEBUG("closed\r\n");

	lvgl_RiLi_main_cont = NULL;



}
