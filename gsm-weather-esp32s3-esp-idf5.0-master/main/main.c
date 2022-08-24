
#include "main.h"
//#include "genghuanlvxin.h"
#include "lvgl_project.h"
//#include "freertosconfig.h"

lv_obj_t * image_dianliang;

void chongdian_gif_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
		case LV_EVENT_LEAVE:
			if(obj==image_dianliang)
			{
				main_debug("重启gif\r\n");
				lv_gif_restart(image_dianliang);
			}
		break;
		case LV_EVENT_DELETE:
			main_debug("删除gif\r\n");
			if(obj==image_dianliang)
			{
				image_dianliang=NULL;
			}
		break;
		case LV_EVENT_RELEASED://对象已被释放
			main_debug("删除\r\n");
			break;
		default:
			break;
	}
}


static const char *TAG = "main";
void app_main()
{
	// char *buf =(char*)heap_caps_malloc(1024*1, MALLOC_CAP_SPIRAM);
	// if(buf==NULL)
	// {
	// 	main_debug("内存申请失败\r\n");
	// }

	main_debug("-------------开始运行----------------\r\n");
	main_debug("esp32 sdk version :%s\n", esp_get_idf_version());

	bsp_key_init();
	bsp_power_init();
    my_spiffs_init();

	bsp_sd_init();
	bsp_ledc_init();

	//multi_button_task_init();

	nvs_init();
	system_init();

	//font_init();

	i2c2_init();
	cst816t_init();
    lcd_init(SPI3_HOST, 80000000);

    lvgl_init();
	lv_port_fs_init();
	lvgl_YangShi_create();
    lvgl_desktop_create(lv_scr_act());

	wifi_init();

    //lvgl_clock_create(lv_scr_act());

	//lv_demo_stress();
	//lv_demo_printer();
	//lv_demo_music();
	//lv_demo_widgets();

	//image_dianliang = lv_gif_create_from_data(lv_scr_act(),genghuanlvxin_gif);
	// image_dianliang = lv_gif_create_from_file(lv_scr_act(),"S:/001.gif");
	// lv_obj_set_event_cb(image_dianliang, chongdian_gif_event_cb);//设置回调函数
	// lv_obj_set_pos(image_dianliang, 0, 0);

	// lv_obj_t *btn_lianjie;
	// btn_lianjie = lv_btn_create(lv_scr_act(),NULL);
	// lv_obj_set_pos(btn_lianjie, 0, 0);
	// lv_obj_set_size(btn_lianjie, 240, 280);
	//vTaskDelay(pdMS_TO_TICKS(1000));
	bsp_ledc_set_duty(5);
	bsp_power_on();
	//lvgl_hint_create(lv_scr_act(),"欢迎使用",200,5);

	// while(bsp_key_read_power_gpio()==1)
	// {
	// 	vTaskDelay(pdMS_TO_TICKS(200));
	// }


	//multi_button_callback_init();
	main_debug("初始化结束");

	// while (1)
	// {
	// 	printf_memory();
	// 	vTaskDelay(5000 / portTICK_PERIOD_MS);
	// }
    // while (1) {
    // //    main_debug("DRAM : [%6d] | PSRAM : [%7d]\r\n",
    // //         heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
    // //         heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    //     vTaskDelay(pdMS_TO_TICKS(2000));
    // }
}
void ptintf_neicun(char *file,int len)
{
    int free_size;

    ESP_LOGW("内存监控", "%s:%d",file,len);
    free_size = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
    printf("内部RAM剩余%d.%dKB  ", free_size/1024,free_size%1024);
    free_size = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    printf("外部PSRAM剩余%d.%dkB\r\n",free_size/1024,free_size%1024);
}
