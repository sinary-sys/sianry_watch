#include "lvgl_desktop.h"
#include "lvgl_Project.h"




_lvgl_desktop_GongNeng_Data lvgl_desktop_GongNeng_Data;
_desktop_ChuangKou desktop_ChuangKou;

lv_obj_t *lvgl_desktop_main_cont = NULL;
lv_style_t lvgl_desktop_style;
lv_task_t * lvgl_desktop_task = NULL;

lv_obj_t *lvgl_desktop_Button[desktop_Button_Num];
lv_obj_t *lvgl_desktop_Label[desktop_Button_Num];
lv_style_t lvgl_desktop_Button_style[desktop_Button_Num];

lv_obj_t *desktop_BUTTON_handle[] =
{
	&desktop_ChuangKou.lvgl_TianQi,
	&desktop_ChuangKou.lvgl_BZhan,
	&desktop_ChuangKou.lvgl_HuangLi,
	&desktop_ChuangKou.lvgl_SheZhi,
	&desktop_ChuangKou.lvgl_RiLi,
	&desktop_ChuangKou.lvgl_YouXi,
	&desktop_ChuangKou.lvgl_YinYue,
	&desktop_ChuangKou.lvgl_ShiPin,
	&desktop_ChuangKou.lvgl_JiSuanQi,
	&desktop_ChuangKou.lvgl_NaoZhong,

};


lv_area_t desktop_BUTTON_area[] =
{
	{5,5,125,65},{135,5,100,65},
	{5,75,155,65},{165,75,70,65},
	{5,145,70,80},{80,145,155,80},
	{5,230,113,75},{123,230,112,75},
	{5,310,155,65},{165,310,70,65},
	{5,380,113,80},{123,380,113,80},

	{5,465,230,130},
};


uint32_t desktop_BUTTON_color[][2]=
{
	{0Xff00ff,0Xbc0cc1},{0X8cc63f,0X678931},
	{0X22b573,0X1a7047},{0X2e3192,0X1e2259},
	{0X998675,0X5b5148},{0X29abe2,0X1f7b9b},
	{0Xd4145a,0X991349},{0Xf7931e,0Xba6919},
	{0Xff00ff,0Xa809ad},{0X8cc63f,0X5c7c2a},
	{0Xa67c52,0X75583d},{0Xd9e021,0X999916},

	{0X333333,0X1c1c1c},
};





void lvgl_desktop_button_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	int i = 0;
	//desktop_DEBUG("cb:%d\r\n", event);
	switch (event)
	{

	case LV_EVENT_PRESSING://对象被连续按下

		break;
	case LV_EVENT_PRESSED://对象已被按下


		break;


	case LV_EVENT_CLICKED://非拖动下释放
		if (lvgl_desktop_GongNeng_Data.DongHua_Flag == false)
		{
			lvgl_desktop_GongNeng_Data.DongHua_Flag = true;
		}
		else
		{
			break;
		}

		for (i = 0; i < desktop_Button_Num; i++)
		{
			if (lvgl_desktop_Button[i] == obj)
			{

				lvgl_desktop_GongNeng_Data.AnXia_Num = i;
				desktop_DEBUG("AnXia_Num:%d\r\n", lvgl_desktop_GongNeng_Data.AnXia_Num);
				break;
			}
		}

		lvgl_desktop_GongNeng_Data.AnXia_button = obj;
		desktop_DongHua_Chu();

	break;



	case LV_EVENT_RELEASED://按钮释放


		break;


	case desktop_event_anXia:
	#if 1
	if (obj == lvgl_desktop_Button[0])
		{
			lvgl_desktop_hidden();
			lvgl_TianQi_create(lv_scr_act());
		}
		else
		if (obj == lvgl_desktop_Button[1])
		{
			lvgl_desktop_hidden();

			lvgl_bilibili_create(lv_scr_act());
		}
		else
		if (obj == lvgl_desktop_Button[2])
		{
			lvgl_desktop_hidden();

			lvgl_LaoHuangLi_create(lv_scr_act());
		}
		else
		if (obj == lvgl_desktop_Button[3])
		{
			lvgl_desktop_hidden();

			lvgl_SheZhi_create(lv_scr_act());
		}
		else
		if (obj == lvgl_desktop_Button[4])
		{
			lvgl_desktop_hidden();

			lvgl_RiLi_create(lv_scr_act());
		}else
		if (obj == lvgl_desktop_Button[5])
		{
			lvgl_hint_create(lv_scr_act(),lvgl_globa_text[0][system_get_Language()],200,3);
		}
		else
		{
			lvgl_hint_create(lv_scr_act(),lvgl_globa_text[0][system_get_Language()],200,3);
			desktop_DongHua_Jin();

			//start_webserver();
		}
		#endif
		lvgl_desktop_GongNeng_Data.DongHua_Flag = false;
	break;

	case LV_EVENT_LONG_PRESSED://按钮长按

		break;
	default:
		break;
	}
}

void lvgl_desktop_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	if (obj == lvgl_desktop_main_cont)
	{
		//desktop_DEBUG("cb:%d\r\n", event);
		switch (event)
		{

		case LV_EVENT_DELETE:

			lvgl_desktop_main_cont = NULL;
			desktop_DEBUG("删除窗口\r\n");
			break;

		case LV_EVENT_PRESSING://对象被持续按下


			break;
		case LV_EVENT_PRESSED://对象已被按下


			break;
		case LV_EVENT_DRAG_END://拖动结束后

			if (lv_obj_get_x(lvgl_desktop_main_cont) != 0)
			{
				if (lv_obj_get_x(lvgl_desktop_main_cont) > 100)
				{
					lvgl_desktop_close();
				}
				else
				{
					lv_obj_set_x(lvgl_desktop_main_cont, 0);
				}
			}
			if (lv_obj_get_y(lvgl_desktop_main_cont) > 0)
			{
				lv_obj_set_y(lvgl_desktop_main_cont, 0);
			}else if (lv_obj_get_y(lvgl_desktop_main_cont) < -(lv_obj_get_height(lvgl_desktop_main_cont)-240))
			{
				lv_obj_set_y(lvgl_desktop_main_cont, -(lv_obj_get_height(lvgl_desktop_main_cont) - 240));
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
lv_style_t lvgl_desktop_BeiJing_style;
void lvgl_desktop_create(lv_obj_t * Fu)
{

	if (lvgl_desktop_main_cont == NULL)
	{

		lv_style_init(&lvgl_desktop_BeiJing_style);
		lv_style_copy(&lvgl_desktop_BeiJing_style, &lvgl_WuBianKuang_cont_style);

		/*渐变色*/
		lv_style_set_bg_opa(&lvgl_desktop_BeiJing_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
		lv_style_set_bg_color(&lvgl_desktop_BeiJing_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_desktop_BeiJing_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色

		lv_obj_add_style(lv_scr_act(), LV_OBJ_PART_MAIN, &lvgl_desktop_BeiJing_style);//设置样式

		lv_style_init(&lvgl_desktop_style);
		lv_style_copy(&lvgl_desktop_style, &lvgl_WuBianKuang_cont_style);
		/*渐变色*/
		lv_style_set_bg_opa(&lvgl_desktop_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
		//lv_style_set_bg_color(&lvgl_desktop_style, LV_STATE_DEFAULT, lv_color_hex(0x1b1d5c));//背景上面颜色
		//lv_style_set_bg_grad_color(&lvgl_desktop_style, LV_STATE_DEFAULT, lv_color_hex(0x5c418d));//背景上面颜色
		lv_style_set_bg_color(&lvgl_desktop_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_desktop_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_dir(&lvgl_desktop_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);//渐变方向

		/*调整渐变色位置*/
		lv_style_set_bg_main_stop(&lvgl_desktop_style, LV_STATE_DEFAULT, 10);
		lv_style_set_bg_main_stop(&lvgl_desktop_style, LV_STATE_DEFAULT, 100);

		//----创建容器----//
		lvgl_desktop_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_desktop_main_cont, 0, 0);
		lv_obj_set_size(lvgl_desktop_main_cont, lv_obj_get_width(Fu), 600);
		//lv_obj_set_drag_parent(lvgl_desktop_main_cont, true); //启用 / 禁用父对象可拖动

		// lv_obj_set_click(lvgl_desktop_main_cont, true); //启用 / 禁用可点击
		// lv_obj_set_drag(lvgl_desktop_main_cont, true);//启用/禁用对象可拖动
		// lv_obj_set_drag_dir(lvgl_desktop_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
		// lv_obj_set_drag_throw(lvgl_desktop_main_cont, false);//启用/禁用拖动后是否有惯性移动

		//lv_obj_set_drag_parent(lvgl_desktop_main_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_desktop_main_cont, LV_OBJ_PART_MAIN, &lvgl_desktop_style);//设置样式
		lv_obj_set_event_cb(lvgl_desktop_main_cont, lvgl_desktop_event_cb);//设置回调函数

#if 1
		for (int i = 0; i < desktop_Button_Num; i++)
		{
			lv_style_init(&lvgl_desktop_Button_style[i]);
			lv_style_copy(&lvgl_desktop_Button_style[i], &lvgl_WuBianKuang_cont_style);
			lv_style_set_radius(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, 10);//圆角
			lv_style_set_shadow_width(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, 0);//阴影宽度
			lv_style_set_shadow_opa(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, LV_OPA_TRANSP);//阴影透明度
			lv_style_set_bg_opa(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
			lv_style_set_bg_color(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(desktop_BUTTON_color[i][0]));//背景上面颜色
			lv_style_set_bg_grad_color(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(desktop_BUTTON_color[i][0]));//背景上面颜色

			lv_style_set_bg_color(&lvgl_desktop_Button_style[i], LV_STATE_PRESSED, lv_color_hex(desktop_BUTTON_color[i][1]));
			lv_style_set_bg_grad_color(&lvgl_desktop_Button_style[i], LV_STATE_PRESSED, lv_color_hex(desktop_BUTTON_color[i][1]));

			lv_style_set_border_color(&lvgl_desktop_Button_style[i], LV_STATE_FOCUSED, LV_COLOR_BLUE);
			lv_style_set_border_color(&lvgl_desktop_Button_style[i], LV_STATE_FOCUSED | LV_STATE_PRESSED, LV_COLOR_NAVY);

			lv_style_set_text_color(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, LV_COLOR_WHITE);
			lv_style_set_text_font(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, (const lv_font_t*)&font_ZiDing_K8_24);

			lv_style_set_transform_height(&lvgl_desktop_Button_style[i], LV_STATE_PRESSED, -5);
			lv_style_set_transform_width(&lvgl_desktop_Button_style[i], LV_STATE_PRESSED, -10);
#if LV_USE_ANIMATION
			//Add a transition to the size change
			static lv_anim_path_t path;
			lv_anim_path_init(&path);
			lv_anim_path_set_cb(&path, lv_anim_path_overshoot);

			lv_style_set_transition_prop_1(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
			lv_style_set_transition_prop_2(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
			lv_style_set_transition_time(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, 200);
			lv_style_set_transition_path(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, &path);
#endif

			lvgl_desktop_Button[i] = lv_btn_create(lvgl_desktop_main_cont,NULL);

			lv_obj_set_pos(lvgl_desktop_Button[i], desktop_BUTTON_area[i].x1, desktop_BUTTON_area[i].y1);
			lv_obj_set_size(lvgl_desktop_Button[i], desktop_BUTTON_area[i].x2, desktop_BUTTON_area[i].y2);

			lv_obj_set_drag_parent(lvgl_desktop_Button[i], true); //启用 / 禁用父对象可拖动

			lv_obj_reset_style_list(lvgl_desktop_Button[i], LV_BTN_PART_MAIN);         /*Remove the styles coming from the theme*/
			lv_obj_add_style(lvgl_desktop_Button[i], LV_BTN_PART_MAIN, &lvgl_desktop_Button_style[i]);//设置样式

			lvgl_desktop_Label[i] = lv_label_create(lvgl_desktop_Button[i], NULL);          /*Add a label to the button*/


			lv_obj_set_event_cb(lvgl_desktop_Button[i], lvgl_desktop_button_cb);//设置 btn3的事件回调
		}
#endif
	if(lvgl_desktop_task==NULL)
		lvgl_desktop_task = lvgl_task_create(lvgl_desktop_TaskCb, 200, LV_TASK_PRIO_LOWEST, NULL);
		desktop_DEBUG("创建窗口\r\n");
	}
	else
	{
		desktop_DEBUG("显示窗口\r\n");
	}
	for (int i = 0; i < desktop_Button_Num; i++)
	{
		lv_label_set_text(lvgl_desktop_Label[i], lvgl_globa_text[i+2][system_get_Language()]);/*Set the labels text*/
	}

	lv_obj_move_background(lvgl_desktop_main_cont);

	lv_obj_set_drag_throw(lvgl_desktop_main_cont, false);//启用/禁用拖动后是否有惯性移动
	lvgl_set_obj_show(lvgl_desktop_main_cont);
	desktop_DongHua_Jin();

	// if(lvgl_desktop_task==NULL)
	// 	lvgl_desktop_task = lvgl_task_create(lvgl_desktop_TaskCb, 200, LV_TASK_PRIO_LOWEST, NULL);
}

void lvgl_desktop_hidden(void)
{
	lvgl_set_obj_hide(lvgl_desktop_main_cont);
	lv_obj_set_click(lvgl_desktop_main_cont, false); //启用 / 禁用可点击
	lv_obj_set_drag(lvgl_desktop_main_cont, false);//启用/禁用对象可拖动
	lv_obj_set_drag_dir(lvgl_desktop_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
}

void lvgl_desktop_close(void)
{

	lvgl_set_obj_hide(lvgl_desktop_main_cont);
	lv_obj_set_x(lvgl_desktop_main_cont,0);
	lvgl_desktop_GongNeng_Data.point.y = lv_obj_get_y(lvgl_desktop_main_cont);
	lvgl_desktop_GongNeng_Data.point.x = lv_obj_get_x(lvgl_desktop_main_cont);

	lvgl_clock_create(lv_scr_act());
}

void lvgl_desktop_TaskCb(lv_task_t *t)
{

	if (lv_obj_get_y(lvgl_desktop_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_desktop_main_cont, true);//启用/禁用拖动后是否有惯性移动
	}

	if (lv_obj_get_x(lvgl_desktop_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_desktop_main_cont, false);//启用/禁用拖动后是否有惯性移动
	}

}

void desktop_anim_01(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_02(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_03(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_04(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_05(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_06(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_07(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_08(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_09(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_10(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_11(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_12(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_13(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void desktop_anim_Jin_ready_cb(lv_anim_t * anim)
{

	desktop_DEBUG("---------执行进动画结束---------\r\n");

	lv_obj_set_click(lvgl_desktop_main_cont, true); //启用 / 禁用可点击
	lv_obj_set_drag(lvgl_desktop_main_cont, true);//启用/禁用对象可拖动
	lv_obj_set_drag_dir(lvgl_desktop_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向

}
void desktop_anim_Chu_ready_cb(lv_anim_t * anim)
{
	desktop_DEBUG("chu ok\r\n");

	lv_event_send(lvgl_desktop_GongNeng_Data.AnXia_button, desktop_event_anXia,NULL);
	//desktop_DongHua_Jin();
}

void(*desktop_anim_cb_buf[desktop_Button_Num])(void * arc, lv_anim_value_t v) =
{
	&desktop_anim_01,
	&desktop_anim_02,
	&desktop_anim_03,
	&desktop_anim_04,
	&desktop_anim_05,
	&desktop_anim_06,
	&desktop_anim_07,
	&desktop_anim_08,
	&desktop_anim_09,
	&desktop_anim_10,
	&desktop_anim_11,
	&desktop_anim_12,
	&desktop_anim_13,
};

//滑入动画
void desktop_DongHua_Jin(void)
{
	int i = 0;
	int max = desktop_Button_Num;


	desktop_DEBUG("---------执行进动画---------\r\n");

	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_overshoot);
	//lv_anim_path_linear线性动画
	//lv_anim_path_step最后一步更改
	//lv_anim_path_ease_in开头很慢
	//lv_anim_path_ease_out最后慢
	//lv_anim_path_ease_in_out在开始和结束时也很慢
	//lv_anim_path_overshoot超出最终值
	//lv_anim_path_bounce从最终值反弹一点（就像撞墙一样）

	for (i = 0; i < max; i++)
	{
		lv_obj_set_y(lvgl_desktop_Button[i], 240);


		lv_anim_init(&desktop_ChuangKou.lv_anim_Jin[i]);
		if (i == max-1)
		{
			lv_anim_set_ready_cb(&desktop_ChuangKou.lv_anim_Jin[i], desktop_anim_Jin_ready_cb);
		}

		lv_anim_set_exec_cb(&desktop_ChuangKou.lv_anim_Jin[i], desktop_anim_cb_buf[i]);
		lv_anim_set_values(&desktop_ChuangKou.lv_anim_Jin[i], 240, desktop_BUTTON_area[i].y1);
		lv_anim_set_time(&desktop_ChuangKou.lv_anim_Jin[i], 200+i*10);
		lv_anim_set_var(&desktop_ChuangKou.lv_anim_Jin[i], lvgl_desktop_Button[i]);

		lv_anim_set_path(&desktop_ChuangKou.lv_anim_Jin[i], &path);
		lv_anim_start(&desktop_ChuangKou.lv_anim_Jin[i]);
		vTaskDelay(pdMS_TO_TICKS(5));
	}


}
void desktop_anim_cb_DongHua(void * arc, lv_anim_value_t v)
{
	lv_obj_set_pos(arc, desktop_ChuangKou.lv_DongHua_area.x1-v/2, desktop_ChuangKou.lv_DongHua_area.y1-v/2);
	lv_obj_set_size(arc, desktop_ChuangKou.lv_DongHua_area.x2+v, desktop_ChuangKou.lv_DongHua_area.y2 + v);

}
void desktop_anim_ready_DongHua_cb(lv_anim_t * anim)
{
	lv_event_send(lvgl_desktop_GongNeng_Data.AnXia_button, desktop_event_anXia, NULL);

	lv_obj_del(desktop_ChuangKou.lvgl_btn_DongHua);
	lv_style_reset(&desktop_ChuangKou.lvgl_btn_DongHua_style);

}
//滑出动画
void desktop_DongHua_Chu(void)
{
	int x = 0, y = 0;

	lv_style_init(&desktop_ChuangKou.lvgl_btn_DongHua_style);
	lv_style_copy(&desktop_ChuangKou.lvgl_btn_DongHua_style, &lvgl_desktop_Button_style[lvgl_desktop_GongNeng_Data.AnXia_Num]);
	lv_style_set_radius(&desktop_ChuangKou.lvgl_btn_DongHua_style, LV_STATE_DEFAULT, 30);//圆角


	desktop_ChuangKou.lvgl_btn_DongHua = lv_btn_create(lv_scr_act(), lvgl_desktop_GongNeng_Data.AnXia_button);

	desktop_ChuangKou.lv_DongHua_area.x1 = lv_obj_get_x(lvgl_desktop_GongNeng_Data.AnXia_button);
	desktop_ChuangKou.lv_DongHua_area.y1 = lv_obj_get_y(lvgl_desktop_GongNeng_Data.AnXia_button);
	desktop_ChuangKou.lv_DongHua_area.x2 = lv_obj_get_width(lvgl_desktop_GongNeng_Data.AnXia_button);
	desktop_ChuangKou.lv_DongHua_area.y2 = lv_obj_get_height(lvgl_desktop_GongNeng_Data.AnXia_button);
	y= lv_obj_get_y(lvgl_desktop_main_cont);
	desktop_ChuangKou.lv_DongHua_area.y1 += lv_obj_get_y(lvgl_desktop_main_cont);

	lv_obj_set_y(desktop_ChuangKou.lvgl_btn_DongHua, desktop_ChuangKou.lv_DongHua_area.y1);

	lvgl_desktop_GongNeng_Data.DongHua_KaiShiZhi = fmin(desktop_ChuangKou.lv_DongHua_area.x2, desktop_ChuangKou.lv_DongHua_area.y2);

	lv_anim_init(&desktop_ChuangKou.lv_DongHua_anim);
	lv_anim_set_ready_cb(&desktop_ChuangKou.lv_DongHua_anim, desktop_anim_ready_DongHua_cb);
	lv_anim_set_exec_cb(&desktop_ChuangKou.lv_DongHua_anim, desktop_anim_cb_DongHua);
	lv_anim_set_values(
		&desktop_ChuangKou.lv_DongHua_anim,
		lvgl_desktop_GongNeng_Data.DongHua_KaiShiZhi,
		400
	);
	lv_anim_set_time(&desktop_ChuangKou.lv_DongHua_anim, 200);
	lv_anim_set_var(&desktop_ChuangKou.lv_DongHua_anim, desktop_ChuangKou.lvgl_btn_DongHua);
	lv_anim_start(&desktop_ChuangKou.lv_DongHua_anim);


/*	int i = 0;
	int max = desktop_Button_Num;
	for (i = 0; i < max-1; i++)
	{
		lv_obj_set_y(lvgl_desktop_Button[i], desktop_BUTTON_area[i].y1);

		lv_anim_init(&desktop_ChuangKou.lv_anim_Chu[i]);
		if (i == max-1)
		{
			lv_anim_set_ready_cb(&desktop_ChuangKou.lv_anim_Chu[i], desktop_anim_Chu_ready_cb);
		}
		lv_anim_set_exec_cb(&desktop_ChuangKou.lv_anim_Chu[i], desktop_anim_cb_buf[i]);

		lv_anim_set_values(&desktop_ChuangKou.lv_anim_Chu[i], desktop_BUTTON_area[i].y1, 240);
		lv_anim_set_time(&desktop_ChuangKou.lv_anim_Chu[i], 200 + i * 10);
		lv_anim_set_var(&desktop_ChuangKou.lv_anim_Chu[i], lvgl_desktop_Button[i]);
		lv_anim_start(&desktop_ChuangKou.lv_anim_Chu[i]);
	}

*/

}

