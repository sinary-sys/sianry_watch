#include "lvgl_LaoHuangLi.h"
#include "lvgl_Project.h"




LV_IMG_DECLARE(bmp_WanNianLi_1)
LV_IMG_DECLARE(bmp_WanNianLi_2)
LV_IMG_DECLARE(bmp_WanNianLi_3)
LV_IMG_DECLARE(bmp_WanNianLi_4)
LV_IMG_DECLARE(bmp_WanNianLi_5)
LV_IMG_DECLARE(bmp_WanNianLi_6)



_lvgl_LaoHuangLi_GongNeng_Data lvgl_LaoHuangLi_GongNeng_Data;

lv_obj_t *lvgl_LaoHuangLi_main_cont = NULL;

lv_obj_t *lvgl_LaoHuangLi_NongLi_cont = NULL;
lv_obj_t *lvgl_LaoHuangLi_YangLi_cont = NULL;


lv_obj_t *lvgl_LaoHuangLi_WuXing_cont = NULL;
lv_obj_t *lvgl_LaoHuangLi_ChongSha_cont = NULL;
lv_obj_t *lvgl_LaoHuangLi_Yi_cont = NULL;
lv_obj_t *lvgl_LaoHuangLi_Ji_cont = NULL;
lv_obj_t *lvgl_LaoHuangLi_JiShenYiQu_cont = NULL;
lv_obj_t *lvgl_LaoHuangLi_XiongShenYiJi_cont = NULL;


lv_style_t lvgl_LaoHuangLi_main_cont_style;
lv_style_t lvgl_LaoHuangLi_TouMing_cont_style;
lv_task_t *lvgl_LaoHuangLi_task = NULL;



//设置农历
void lvgl_LaoHuangLi_Set_YinLi(char *str)
{
	char buf[20];
	static lv_obj_t *lvgl_Text = NULL;
	if (lvgl_LaoHuangLi_NongLi_cont == NULL)
	{
		//----创建容器----//
		lvgl_LaoHuangLi_NongLi_cont = lv_cont_create(lvgl_LaoHuangLi_main_cont, NULL);
		lv_obj_set_pos(lvgl_LaoHuangLi_NongLi_cont, 0, 7);
		lv_obj_set_size(lvgl_LaoHuangLi_NongLi_cont, 240, 32);
		lv_obj_set_drag_parent(lvgl_LaoHuangLi_NongLi_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_LaoHuangLi_NongLi_cont, LV_OBJ_PART_MAIN, &lvgl_LaoHuangLi_TouMing_cont_style);


		lvgl_Text = lv_label_create(lvgl_LaoHuangLi_NongLi_cont, NULL);
		lv_label_set_long_mode(lvgl_Text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_Text, 0, 0);
		lv_obj_set_width(lvgl_Text, 240);
		lv_obj_set_height(lvgl_Text, 32);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_align(lvgl_Text, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_text(lvgl_Text, str);

		lv_obj_add_style(lvgl_Text, LV_OBJ_PART_MAIN, &lvgl_font24_style);

		lv_label_set_anim_speed(lvgl_Text, 20);


	}
	if (str == NULL)
	{

		lv_label_set_text(lvgl_Text, "---------");
		return;
	}

	lv_label_set_text(lvgl_Text, str);
}

//设置阳历
void lvgl_LaoHuangLi_Set_YangLi(char *str)
{
	char buf[20];
	static lv_obj_t *lvgl_Text = NULL;
	if (lvgl_LaoHuangLi_YangLi_cont == NULL)
	{
		//----创建容器----//
		lvgl_LaoHuangLi_YangLi_cont = lv_cont_create(lvgl_LaoHuangLi_main_cont, NULL);
		lv_obj_set_pos(lvgl_LaoHuangLi_YangLi_cont, 0, 40);
		lv_obj_set_size(lvgl_LaoHuangLi_YangLi_cont, 240, 32);
		lv_obj_set_drag_parent(lvgl_LaoHuangLi_YangLi_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_LaoHuangLi_YangLi_cont, LV_OBJ_PART_MAIN, &lvgl_LaoHuangLi_TouMing_cont_style);


		lvgl_Text = lv_label_create(lvgl_LaoHuangLi_YangLi_cont, NULL);
		lv_label_set_long_mode(lvgl_Text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_Text, 0, 0);
		lv_obj_set_width(lvgl_Text, 240);
		lv_obj_set_height(lvgl_Text, 24);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_align(lvgl_Text, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_text(lvgl_Text, str);

		lv_obj_add_style(lvgl_Text, LV_OBJ_PART_MAIN, &lvgl_font16_style);

		lv_label_set_anim_speed(lvgl_Text, 20);


	}
	if (str == NULL)
	{

		lv_label_set_text(lvgl_Text, " ");
		return;
	}

	lv_label_set_text(lvgl_Text, str);
}
//设置五行
void lvgl_LaoHuangLi_Set_WuXing(char *str)
{
	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_Text = NULL;
	if (lvgl_LaoHuangLi_WuXing_cont == NULL)
	{
		//----创建容器----//
		lvgl_LaoHuangLi_WuXing_cont = lv_cont_create(lvgl_LaoHuangLi_main_cont, NULL);
		lv_obj_set_pos(lvgl_LaoHuangLi_WuXing_cont, 0, 62);
		lv_obj_set_size(lvgl_LaoHuangLi_WuXing_cont, 240, 30);
		lv_obj_set_drag_parent(lvgl_LaoHuangLi_WuXing_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_LaoHuangLi_WuXing_cont, LV_OBJ_PART_MAIN, &lvgl_LaoHuangLi_TouMing_cont_style);

		lvgl_TuBiao_image = lv_img_create(lvgl_LaoHuangLi_WuXing_cont, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 17, 0);
		lv_img_set_src(lvgl_TuBiao_image, &bmp_WanNianLi_1);

		lvgl_Text = lv_label_create(lvgl_LaoHuangLi_WuXing_cont, NULL);
		lv_label_set_long_mode(lvgl_Text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_Text, 61, 2);
		lv_obj_set_width(lvgl_Text, 168);
		lv_obj_set_height(lvgl_Text, 24);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_align(lvgl_Text, LV_LABEL_ALIGN_LEFT);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_text(lvgl_Text, str);

		lv_obj_add_style(lvgl_Text, LV_OBJ_PART_MAIN, &lvgl_font16_style);

		lv_label_set_anim_speed(lvgl_Text, 20);


	}
	if (str==NULL)
	{

		lv_label_set_text(lvgl_Text, "---------");
		return;
	}

	lv_label_set_text(lvgl_Text, str);
}

//设置冲煞
void lvgl_LaoHuangLi_Set_ChongSha(char *str)
{
	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_Text = NULL;
	if (lvgl_LaoHuangLi_ChongSha_cont == NULL)
	{
		//----创建容器----//
		lvgl_LaoHuangLi_ChongSha_cont = lv_cont_create(lvgl_LaoHuangLi_main_cont, NULL);
		lv_obj_set_pos(lvgl_LaoHuangLi_ChongSha_cont, 0, 98);
		lv_obj_set_size(lvgl_LaoHuangLi_ChongSha_cont, 240, 30);
		lv_obj_set_drag_parent(lvgl_LaoHuangLi_ChongSha_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_LaoHuangLi_ChongSha_cont, LV_OBJ_PART_MAIN, &lvgl_LaoHuangLi_TouMing_cont_style);

		lvgl_TuBiao_image = lv_img_create(lvgl_LaoHuangLi_ChongSha_cont, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 17, 0);
		lv_img_set_src(lvgl_TuBiao_image, &bmp_WanNianLi_2);

		lvgl_Text = lv_label_create(lvgl_LaoHuangLi_ChongSha_cont, NULL);
		lv_label_set_long_mode(lvgl_Text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_Text, 61, 2);
		lv_obj_set_width(lvgl_Text, 168);
		lv_obj_set_height(lvgl_Text, 24);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_align(lvgl_Text, LV_LABEL_ALIGN_LEFT);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_text(lvgl_Text, str);

		lv_obj_add_style(lvgl_Text, LV_OBJ_PART_MAIN, &lvgl_font16_style);

		lv_label_set_anim_speed(lvgl_Text, 20);


	}
	if (str == NULL)
	{

		lv_label_set_text(lvgl_Text, "---------");
		return;
	}

	lv_label_set_text(lvgl_Text, str);
}
//设置宜
void lvgl_LaoHuangLi_Set_Yi(char *str)
{
	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_Text = NULL;
	if (lvgl_LaoHuangLi_Yi_cont == NULL)
	{
		//----创建容器----//
		lvgl_LaoHuangLi_Yi_cont = lv_cont_create(lvgl_LaoHuangLi_main_cont, NULL);
		lv_obj_set_pos(lvgl_LaoHuangLi_Yi_cont, 0, 134);
		lv_obj_set_size(lvgl_LaoHuangLi_Yi_cont, 240, 30);
		lv_obj_set_drag_parent(lvgl_LaoHuangLi_Yi_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_LaoHuangLi_Yi_cont, LV_OBJ_PART_MAIN, &lvgl_LaoHuangLi_TouMing_cont_style);

		lvgl_TuBiao_image = lv_img_create(lvgl_LaoHuangLi_Yi_cont, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 17, 0);
		lv_img_set_src(lvgl_TuBiao_image, &bmp_WanNianLi_3);

		lvgl_Text = lv_label_create(lvgl_LaoHuangLi_Yi_cont, NULL);
		lv_label_set_long_mode(lvgl_Text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_Text, 61, 2);
		lv_obj_set_width(lvgl_Text, 168);
		lv_obj_set_height(lvgl_Text, 24);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_align(lvgl_Text, LV_LABEL_ALIGN_LEFT);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_text(lvgl_Text, str);

		lv_obj_add_style(lvgl_Text, LV_OBJ_PART_MAIN, &lvgl_font16_style);

		lv_label_set_anim_speed(lvgl_Text, 20);


	}
	if (str == NULL)
	{

		lv_label_set_text(lvgl_Text, "---------");
		return;
	}

	lv_label_set_text(lvgl_Text, str);
}
//设置忌
void lvgl_LaoHuangLi_Set_Ji(char *str)
{
	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_Text = NULL;
	if (lvgl_LaoHuangLi_Ji_cont == NULL)
	{
		//----创建容器----//
		lvgl_LaoHuangLi_Ji_cont = lv_cont_create(lvgl_LaoHuangLi_main_cont, NULL);
		lv_obj_set_pos(lvgl_LaoHuangLi_Ji_cont, 0, 170);
		lv_obj_set_size(lvgl_LaoHuangLi_Ji_cont, 240, 30);
		lv_obj_set_drag_parent(lvgl_LaoHuangLi_Ji_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_LaoHuangLi_Ji_cont, LV_OBJ_PART_MAIN, &lvgl_LaoHuangLi_TouMing_cont_style);

		lvgl_TuBiao_image = lv_img_create(lvgl_LaoHuangLi_Ji_cont, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 17, 0);
		lv_img_set_src(lvgl_TuBiao_image, &bmp_WanNianLi_4);

		lvgl_Text = lv_label_create(lvgl_LaoHuangLi_Ji_cont, NULL);
		lv_label_set_long_mode(lvgl_Text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_Text, 61, 2);
		lv_obj_set_width(lvgl_Text, 168);
		lv_obj_set_height(lvgl_Text, 24);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_align(lvgl_Text, LV_LABEL_ALIGN_LEFT);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_text(lvgl_Text, str);

		lv_obj_add_style(lvgl_Text, LV_OBJ_PART_MAIN, &lvgl_font16_style);

		lv_label_set_anim_speed(lvgl_Text, 20);


	}
	if (str == NULL)
	{

		lv_label_set_text(lvgl_Text, "---------");
		return;
	}

	lv_label_set_text(lvgl_Text, str);
}
//设置吉神宜趋
void lvgl_LaoHuangLi_Set_JiShenYiQu(char *str)
{
	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_Text = NULL;
	if (lvgl_LaoHuangLi_JiShenYiQu_cont == NULL)
	{
		//----创建容器----//
		lvgl_LaoHuangLi_JiShenYiQu_cont = lv_cont_create(lvgl_LaoHuangLi_main_cont, NULL);
		lv_obj_set_pos(lvgl_LaoHuangLi_JiShenYiQu_cont, 0, 207);
		lv_obj_set_size(lvgl_LaoHuangLi_JiShenYiQu_cont, 240, 30);
		lv_obj_set_drag_parent(lvgl_LaoHuangLi_JiShenYiQu_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_LaoHuangLi_JiShenYiQu_cont, LV_OBJ_PART_MAIN, &lvgl_LaoHuangLi_TouMing_cont_style);

		lvgl_TuBiao_image = lv_img_create(lvgl_LaoHuangLi_JiShenYiQu_cont, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 2, 3);
		lv_img_set_src(lvgl_TuBiao_image, &bmp_WanNianLi_5);

		lvgl_Text = lv_label_create(lvgl_LaoHuangLi_JiShenYiQu_cont, NULL);
		lv_label_set_long_mode(lvgl_Text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_Text, 61, 2);
		lv_obj_set_width(lvgl_Text, 168);
		lv_obj_set_height(lvgl_Text, 24);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_align(lvgl_Text, LV_LABEL_ALIGN_LEFT);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_text(lvgl_Text, str);

		lv_obj_add_style(lvgl_Text, LV_OBJ_PART_MAIN, &lvgl_font16_style);

		lv_label_set_anim_speed(lvgl_Text, 20);


	}
	if (str == NULL)
	{

		lv_label_set_text(lvgl_Text, "---------");
		return;
	}

	lv_label_set_text(lvgl_Text, str);
}

//设置凶神宜忌
void lvgl_LaoHuangLi_Set_XiongShenYiJi(char *str)
{
	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_Text = NULL;
	if (lvgl_LaoHuangLi_XiongShenYiJi_cont == NULL)
	{
		//----创建容器----//
		lvgl_LaoHuangLi_XiongShenYiJi_cont = lv_cont_create(lvgl_LaoHuangLi_main_cont, NULL);
		lv_obj_set_pos(lvgl_LaoHuangLi_XiongShenYiJi_cont, 0, 245);
		lv_obj_set_size(lvgl_LaoHuangLi_XiongShenYiJi_cont, 240, 30);
		lv_obj_set_drag_parent(lvgl_LaoHuangLi_XiongShenYiJi_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_LaoHuangLi_XiongShenYiJi_cont, LV_OBJ_PART_MAIN, &lvgl_LaoHuangLi_TouMing_cont_style);

		lvgl_TuBiao_image = lv_img_create(lvgl_LaoHuangLi_XiongShenYiJi_cont, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 2, 3);
		lv_img_set_src(lvgl_TuBiao_image, &bmp_WanNianLi_6);

		lvgl_Text = lv_label_create(lvgl_LaoHuangLi_XiongShenYiJi_cont, NULL);
		lv_label_set_long_mode(lvgl_Text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_Text, 61, 2);
		lv_obj_set_width(lvgl_Text, 168);
		lv_obj_set_height(lvgl_Text, 24);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_align(lvgl_Text, LV_LABEL_ALIGN_LEFT);
		lv_label_set_recolor(lvgl_Text, true);
		lv_label_set_text(lvgl_Text, str);

		lv_obj_add_style(lvgl_Text, LV_OBJ_PART_MAIN, &lvgl_font16_style);

		lv_label_set_anim_speed(lvgl_Text, 20);


	}
	if (str == NULL)
	{

		lv_label_set_text(lvgl_Text, "---------");
		return;
	}

	lv_label_set_text(lvgl_Text, str);
}

void lvgl_LaoHuangLi_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{


	//printf("cb:%d\r\n", event);
	switch (event)
	{

		case lvgl_shuaxin_jieshu_event:

			lvgl_LaoHuangLi_ShuaXin_jieshu();
		break;

		case LV_EVENT_DELETE:

			lvgl_LaoHuangLi_main_cont = NULL;
			LaoHuangLi_DEBUG("删除窗口\r\n");
		break;
		case LV_EVENT_PRESSING://对象被持续按下

			//if (lv_obj_get_y(lvgl_LaoHuangLi_main_cont) > 70)
			//{
			//
			//	lvgl_ShuaXin_Start(30);
			//}

		break;
		case LV_EVENT_PRESSED://对象已被按下


		break;
		case LV_EVENT_DRAG_END://拖动结束后

			if (lv_obj_get_x(lvgl_LaoHuangLi_main_cont) != 0)
			{
				if (lv_obj_get_x(lvgl_LaoHuangLi_main_cont) > 50)
				{
					lvgl_LaoHuangLi_close();
				}
				else
				{
					lv_obj_set_x(lvgl_LaoHuangLi_main_cont, 0);
				}
			}

			if (lv_obj_get_y(lvgl_LaoHuangLi_main_cont) > lvgl_ShuaXin_GaoDu)
			{

				lvgl_LaoHuangLi_ShuaXin_kaishi();


			}
			else if(lv_obj_get_y(lvgl_LaoHuangLi_main_cont) > 0&& lv_obj_get_y(lvgl_LaoHuangLi_main_cont)< lvgl_ShuaXin_GaoDu)
			{

				lv_obj_set_y(lvgl_LaoHuangLi_main_cont, 0);
			}


			if (lv_obj_get_y(lvgl_LaoHuangLi_main_cont) < 0)
			{

				lv_obj_set_y(lvgl_LaoHuangLi_main_cont, 0);
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


void lvgl_LaoHuangLi_create(lv_obj_t * Fu)
{



	if (lvgl_LaoHuangLi_main_cont == NULL)
	{




		lv_style_init(&lvgl_LaoHuangLi_main_cont_style);
		lv_style_copy(&lvgl_LaoHuangLi_main_cont_style, &lvgl_WuBianKuang_cont_style);


		//----透明背景容器样式----//
		lv_style_init(&lvgl_LaoHuangLi_TouMing_cont_style);
		lv_style_set_radius(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, 0);
		lv_style_set_border_opa(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, 255);//边框透明度
		lv_style_set_border_width(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, 0);//边框宽度
		lv_style_set_border_side(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_NONE);
		lv_style_set_border_blend_mode(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, LV_BLEND_MODE_NORMAL);
		lv_style_set_pad_top(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, 0);//内边距上侧尺寸
		lv_style_set_pad_bottom(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, 0);//内边距下侧尺寸
		lv_style_set_pad_left(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, 0);//内边距左侧尺寸
		lv_style_set_pad_right(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, 0);//内边距右侧尺寸
		//背景
		lv_style_set_bg_opa(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, LV_OPA_0);//背景透明度
		lv_style_set_bg_color(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x5B, 0x97));//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_LaoHuangLi_TouMing_cont_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x93, 0x93, 0x93));//背景下面颜色

		//----透明背景容器样式----//


		//----创建容器----//
		lvgl_LaoHuangLi_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_LaoHuangLi_main_cont, 0, 0);
		lv_obj_set_size(lvgl_LaoHuangLi_main_cont, lv_obj_get_width(Fu), lv_obj_get_height(Fu));

		lv_obj_set_click(lvgl_LaoHuangLi_main_cont, true); //启用 / 禁用可点击
		lv_obj_set_drag(lvgl_LaoHuangLi_main_cont, true);//启用/禁用对象可拖动
		lv_obj_set_drag_dir(lvgl_LaoHuangLi_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
		//lv_obj_set_drag_throw(lvgl_LaoHuangLi_main_cont, true);//启用/禁用拖动后是否有惯性移动
		//lv_obj_set_drag_parent(lvgl_LaoHuangLi_main_cont, true); //启用 / 禁用父对象可拖动

		lv_obj_add_style(lvgl_LaoHuangLi_main_cont, LV_OBJ_PART_MAIN, &lvgl_LaoHuangLi_main_cont_style);//设置样式
		lv_obj_set_event_cb(lvgl_LaoHuangLi_main_cont, lvgl_LaoHuangLi_event_cb);//设置回调函数


		lvgl_LaoHuangLi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_JieShu;

#if lvgl_win
		lvgl_LaoHuangLi_Set_WuXing("乙不栽植千株不长 酉不宴客醉坐颠狂");
		lvgl_LaoHuangLi_Set_ChongSha("乙不栽植千株不长 酉不宴客醉坐颠狂");
		lvgl_LaoHuangLi_Set_Yi("乙不栽植千株不长 酉不宴客醉坐颠狂");
		lvgl_LaoHuangLi_Set_Ji("乙不栽植千株不长 酉不宴客醉坐颠狂");
		lvgl_LaoHuangLi_Set_JiShenYiQu("乙不栽植千株不长 酉不宴客醉坐颠狂");
		lvgl_LaoHuangLi_Set_XiongShenYiJi("乙不栽植千株不长 酉不宴客醉坐颠狂");
		lvgl_LaoHuangLi_Set_YinLi("庚子(鼠)年九月十七");
		lvgl_LaoHuangLi_Set_YangLi("2020-11-02");
#else
		lvgl_LaoHuangLi_Set_WuXing(NULL);
		lvgl_LaoHuangLi_Set_ChongSha(NULL);
		lvgl_LaoHuangLi_Set_Yi(NULL);
		lvgl_LaoHuangLi_Set_Ji(NULL);
		lvgl_LaoHuangLi_Set_JiShenYiQu(NULL);
		lvgl_LaoHuangLi_Set_XiongShenYiJi(NULL);
		lvgl_LaoHuangLi_Set_YinLi("下拉刷新");
		lvgl_LaoHuangLi_Set_YangLi(NULL);
#endif


		system_data.HuoQu_LaoHuangLi_Flag = true;//更新老黄历
		LaoHuangLi_DEBUG("创建窗口\r\n");
	}
	else
	{

		LaoHuangLi_DEBUG("显示窗口\r\n");
	}

	lv_obj_move_background(lvgl_LaoHuangLi_main_cont);

	lvgl_set_obj_show(lvgl_LaoHuangLi_main_cont);
	lvgl_LaoHuangLi_task = lvgl_task_create(lvgl_LaoHuangLi_TaskCb, 1000, LV_TASK_PRIO_LOWEST, NULL);

	lvgl_LaoHuangLi_DongHua_Jin();

	// static uint8_t flag=0;

	// if(flag==0)
	// {
	// 	flag=1;
	// 	lvgl_LaoHuangLi_shuaxin_kaishi();
	// }




}


void lvgl_LaoHuangLi_close(void)
{

	lvgl_task_delete(lvgl_LaoHuangLi_task);

	lvgl_set_obj_hide(lvgl_LaoHuangLi_main_cont);

	lv_obj_set_pos(lvgl_LaoHuangLi_main_cont, 0, 0);

	lvgl_desktop_create(lv_scr_act());

}


//滑入动画
void lvgl_LaoHuangLi_DongHua_Jin(void)
{
	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
	//lv_anim_path_linear线性动画
	//lv_anim_path_step最后一步更改
	//lv_anim_path_ease_in开头很慢
	//lv_anim_path_ease_out最后慢
	//lv_anim_path_ease_in_out在开始和结束时也很慢
	//lv_anim_path_overshoot超出最终值
	//lv_anim_path_bounce从最终值反弹一点（就像撞墙一样）


	lv_obj_set_x(lvgl_LaoHuangLi_WuXing_cont, 250);
	lv_obj_set_x(lvgl_LaoHuangLi_ChongSha_cont, 250);
	lv_obj_set_x(lvgl_LaoHuangLi_Yi_cont, 250);
	lv_obj_set_x(lvgl_LaoHuangLi_Ji_cont, 250);
	lv_obj_set_x(lvgl_LaoHuangLi_JiShenYiQu_cont, 250);
	lv_obj_set_x(lvgl_LaoHuangLi_XiongShenYiJi_cont, 250);

	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing, lvgl_LaoHuangLi_anim_WuXing_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing, 250,0);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing, 100);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing, lvgl_LaoHuangLi_WuXing_cont);
	lv_anim_set_path(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing, &path);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing);


	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha, lvgl_LaoHuangLi_anim_ChongSha_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha, 250, 0);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha, 200);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha, lvgl_LaoHuangLi_ChongSha_cont);
	lv_anim_set_path(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha, &path);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha);




	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi, lvgl_LaoHuangLi_anim_Yi_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi, 250, 0);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi, 300);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi, lvgl_LaoHuangLi_Yi_cont);
	lv_anim_set_path(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi, &path);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi);

	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji, lvgl_LaoHuangLi_anim_Ji_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji, 250, 0);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji, 400);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji, lvgl_LaoHuangLi_Ji_cont);
	lv_anim_set_path(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji, &path);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji);

	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu, lvgl_LaoHuangLi_anim_JiShenYiQu_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu, 250, 0);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu, 500);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu, lvgl_LaoHuangLi_JiShenYiQu_cont);
	lv_anim_set_path(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu, &path);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu);

	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi, lvgl_LaoHuangLi_anim_XiongShenYiJi_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi, 250, 0);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi, 600);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi, lvgl_LaoHuangLi_XiongShenYiJi_cont);
	lv_anim_set_path(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi, &path);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi);
}
//滑出动画
void lvgl_LaoHuangLi_DongHua_Chu(void)
{

	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing, lvgl_LaoHuangLi_anim_WuXing_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing, 0, -250);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing, 100);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing, lvgl_LaoHuangLi_WuXing_cont);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_WuXing);


	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha, lvgl_LaoHuangLi_anim_ChongSha_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha, 0, -250);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha, 200);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha, lvgl_LaoHuangLi_ChongSha_cont);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_ChongSha);




	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi, lvgl_LaoHuangLi_anim_Yi_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi, 0, -250);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi, 300);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi, lvgl_LaoHuangLi_Yi_cont);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Yi);

	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji, lvgl_LaoHuangLi_anim_Ji_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji, 0, -250);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji, 400);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji, lvgl_LaoHuangLi_Ji_cont);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_Ji);

	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu, lvgl_LaoHuangLi_anim_JiShenYiQu_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu, 0, -250);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu, 500);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu, lvgl_LaoHuangLi_JiShenYiQu_cont);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_JiShenYiQu);

	lv_anim_init(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi);
	lv_anim_set_exec_cb(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi, lvgl_LaoHuangLi_anim_XiongShenYiJi_cb);
	lv_anim_set_values(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi, 0, -250);
	lv_anim_set_time(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi, 600);
	lv_anim_set_var(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi, lvgl_LaoHuangLi_XiongShenYiJi_cont);
	lv_anim_start(&lvgl_LaoHuangLi_GongNeng_Data.lv_anim_XiongShenYiJi);


}

void lvgl_LaoHuangLi_TaskCb(lv_task_t *t)
{
	static int time = 0;


#if lvgl_win
	if (system_data.HuoQu_LaoHuangLi_Flag == true&&lvgl_shuaxin_get_sta() == lvgl_ShuaXin_Zhong)
	{
		if (++time > 2)
		{
			time = 0;
			lvgl_ShuaXin_close();
		}

	}
#endif

}
//刷新开始
void lvgl_LaoHuangLi_ShuaXin_kaishi(void)
{
	LaoHuangLi_DEBUG("刷新开始\r\n");

	lvgl_LaoHuangLi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_Zhong;

	lv_obj_set_drag(lvgl_LaoHuangLi_main_cont, false);//启用/禁用对象可拖动
	lvgl_LaoHuangLi_DongHua_Chu();

	lvgl_ShuaXin_Start(lvgl_LaoHuangLi_main_cont,&system_data.HuoQu_LaoHuangLi_Flag,30);


}
void lvgl_LaoHuangLi_ShuaXin_jieshu(void)
{

	LaoHuangLi_DEBUG("老黄历刷新 OK\r\n");

	lvgl_LaoHuangLi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_JieShu;
	lvgl_LaoHuangLi_DongHua_Jin();

	lv_obj_set_drag_dir(lvgl_LaoHuangLi_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
}


void lvgl_LaoHuangLi_anim_WuXing_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void lvgl_LaoHuangLi_anim_ChongSha_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void lvgl_LaoHuangLi_anim_Yi_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void lvgl_LaoHuangLi_anim_Ji_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void lvgl_LaoHuangLi_anim_JiShenYiQu_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void lvgl_LaoHuangLi_anim_XiongShenYiJi_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}

