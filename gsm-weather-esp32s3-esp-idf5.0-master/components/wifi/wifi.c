#include "wifi.h"
#include "freertos/task.h"
#include "webserver.h"


extern httpd_handle_t  start_webserver(void);
extern void stop_webserver(void);

_wifi_data wifi_data;

void wifi_lianjie_chenggong(void *event);
void wifi_lianjie_shibai(void);

const char*wifi_TEXT[][SYSTEM_LANGUAGE_NUM] =
{
	{ "WIFI未连接", "WIFI未連接", "WiFi Not Connected", NULL},
	{ "WIFI已连接", "WIFI已連接", "WiFi Connected", NULL},
  { "WIFI已断开", "WIFI已斷開", "WiFi Disconnected", NULL},
  { "WIFI连接失败", "WIFI連接失敗", "WiFi connection failed", NULL},
};


static portMUX_TYPE cdc_acm_lock = portMUX_INITIALIZER_UNLOCKED;
#define ENTER_CRITICAL()   //portENTER_CRITICAL(&cdc_acm_lock)
#define EXIT_CRITICAL()    //portEXIT_CRITICAL(&cdc_acm_lock)


static void https_request_by_get_task(void *pvParameters)
{
  int i=0;
  int res;
  int count=0;

  while(1)
  {

    xSemaphoreTake(system_data.https_request_Semaphore, portMAX_DELAY);//等待信号量

    count = uxSemaphoreGetCount(system_data.https_request_Semaphore);//获取信号的值
    WIFI_DEBUG("计数信号量的值:%d\r\n",count);

    ENTER_CRITICAL();

    if(system_data.wifi_scan_flag == true)
    {
      system_data.wifi_scan_flag=2;

      system_data.HuoQu_bilibili_Flag = false;
      system_data.HuoQu_ShiJian_Flag = false;
      system_data.HuoQu_LaoHuangLi_Flag =false;
      system_data.HuoQu_TianQi_Flag =false;

      wifi_scan_list_start();
      continue ;
    }

    if(system_data.WIFI_Sta!=wifi_yilianjie)
    {
      WIFI_DEBUG("wifi未连接\r\n");


      vTaskDelay(1000 / portTICK_PERIOD_MS);
      lvgl_hint_create(lv_scr_act(),wifi_TEXT[0][system_get_Language()],200,3);


      wifi_lianjie(system_data.wifi_name,system_data.wifi_password,NULL);

      system_data.HuoQu_bilibili_Flag = false;
      system_data.HuoQu_ShiJian_Flag = false;
      system_data.HuoQu_LaoHuangLi_Flag =false;
      system_data.HuoQu_TianQi_Flag =false;

      lvgl_ShuaXin_close();
      goto exit;
    }

    if(system_data.HuoQu_bilibili_Flag == true)
     {
       if(system_data.WIFI_Sta==wifi_yilianjie)
       {

        res = https_get_bilibili_fensi();
        if(res==0)
        {
          lvgl_bilibili_Set_fensi(system_data.bilibili_Data.fensi);
          lvgl_bilibili_Set_guanzhu(system_data.bilibili_Data.guanzhu);
        }
        //res =  https_get_bilibili_bofang();
        if(res==0)
        {
          lvgl_bilibili_Set_bofang(system_data.bilibili_Data.bofang);
        }

       }
       system_data.HuoQu_bilibili_Flag = false;
       lvgl_ShuaXin_close();
     }

    if(system_data.HuoQu_ShiJian_Flag==true||strstr(system_data.RiQi_Data.riqi,"-")==NULL)
    {

      res = HTTP_Get_ShiJian(&system_data.RiQi_Data);
      if(res==0)
      {

        //if(clock_Data.Fen!=system_data.RiQi_Data.fen)
       // {
          //clock_Data.Miao = system_data.RiQi_Data.miao;
          clock_Data.Fen  = system_data.RiQi_Data.fen;
          clock_Data.Shi  = system_data.RiQi_Data.shi;
          clock_Data.Nian = system_data.RiQi_Data.nian;
          clock_Data.Yue  = system_data.RiQi_Data.yue;
          clock_Data.Ri   = system_data.RiQi_Data.ri;

        //}
          WIFI_DEBUG("同步时间: %02d:%02d:%02d\r\n",clock_Data.Shi,clock_Data.Fen,clock_Data.Miao);

      }else
      {


      }
      system_data.HuoQu_ShiJian_Flag = false;
    }

   if(system_data.HuoQu_LaoHuangLi_Flag==true)
    {
      if(system_data.WIFI_Sta==wifi_yilianjie)
      {
        lvgl_LaoHuangLi_Set_YinLi("正在获取...");
        res = https_get_LaoHuangLi(system_data.RiQi_Data.riqi,&system_data.laohuangli_data);
        if(res==0)
        {

          lvgl_LaoHuangLi_Set_WuXing(system_data.laohuangli_data.wuxing);
          lvgl_LaoHuangLi_Set_ChongSha(system_data.laohuangli_data.chongsha);
          lvgl_LaoHuangLi_Set_Yi(system_data.laohuangli_data.yi);
          lvgl_LaoHuangLi_Set_Ji(system_data.laohuangli_data.ji);
          lvgl_LaoHuangLi_Set_JiShenYiQu(system_data.laohuangli_data.jishen);
          lvgl_LaoHuangLi_Set_XiongShenYiJi(system_data.laohuangli_data.xiongshen);
          lvgl_LaoHuangLi_Set_YinLi(system_data.laohuangli_data.yinli);
          lvgl_LaoHuangLi_Set_YangLi(system_data.laohuangli_data.yangli);

        }else if(res==-1)
        {
          lvgl_LaoHuangLi_Set_YinLi("超过每日可允许请求次数!");
        }else if(res==-2)
        {
          lvgl_LaoHuangLi_Set_YinLi("参数错误!");
        }else if(res==-2)
        {
          lvgl_LaoHuangLi_Set_YinLi("获取失败!");
        }

      }else
      {
        lvgl_LaoHuangLi_Set_YinLi("WIFI未连接");

      }

      system_data.HuoQu_LaoHuangLi_Flag = false;
      lvgl_ShuaXin_close();
    }


   if(system_data.HuoQu_TianQi_Flag==true)
    {
      lvgl_TianQi_Set_ChengShi("正在获取...");
      if(system_data.WIFI_Sta==wifi_yilianjie)
      {
        res = https_get_TianQi();

        if(res<-2)
        {
            //xEventGroupSetBits(system_data.TianQi_event_group, BIT0);
          lvgl_TianQi_Set_ChengShi(system_data.City);
          lvgl_TianQi_Set_RiChuRiLuo(0,0,0,0,system_data.RiLuo_Data[0].sunrise,system_data.RiLuo_Data[0].sunset);

            lvgl_TianQi_Set_DangTianQi(
                0,
            atoi(system_data.Weather_Data[0].code_day),
            atoi(system_data.Weather_Data[0].high),
            system_data.Weather_Data[0].text_day,
            atoi(system_data.Weather_Data[0].low),
            atoi(system_data.Weather_Data[0].high)
            );

            lvgl_TianQi_Set_TianQi_JinTian(
            0,
            atoi(system_data.Weather_Data[0].code_day),
            "今天",
            atoi(system_data.Weather_Data[0].low),
            atoi(system_data.Weather_Data[0].high)
            );

            lvgl_TianQi_Set_TianQi_MingTian(
            0,
            atoi(system_data.Weather_Data[1].code_day),
            "明天",
            atoi(system_data.Weather_Data[1].low),
            atoi(system_data.Weather_Data[1].high)
            );

            lvgl_TianQi_Set_TianQi_HouTian(
            0,
            atoi(system_data.Weather_Data[2].code_day),
            "后天",
            atoi(system_data.Weather_Data[2].low),
            atoi(system_data.Weather_Data[2].high)
            );

            lvgl_TianQi_Set_FengSu(system_data.Weather_Data[0].wind_scale);
            lvgl_TianQi_Set_FengXiang(system_data.Weather_Data[0].wind_direction);
            lvgl_TianQi_Set_JiangShui(system_data.Weather_Data[0].rainfall);
            lvgl_TianQi_Set_ShiDu(system_data.Weather_Data[0].humidity);
        }else if(res < 0)
        {


        }

      }
      else

      {
        lvgl_TianQi_Set_ChengShi("WIFI未连接");

      }
      system_data.HuoQu_TianQi_Flag =false;
      lvgl_ShuaXin_close();
    }

exit:
    EXIT_CRITICAL();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}


#if 0
static esp_err_t wifi_event_handler(void *ctx, system_event_t *event)
{
  static int err_code;
  WIFI_DEBUG("消息ID:%d\r\n",event->event_id);
  switch (event->event_id)
  {


    case SYSTEM_EVENT_SCAN_DONE:
      WIFI_DEBUG("扫描结束\r\n");
      wifi_scan_list_get();


    break;


    case SYSTEM_EVENT_ETH_STOP:
      WIFI_DEBUG("以太网停止\r\n");
    break;


  case SYSTEM_EVENT_WIFI_READY:
    WIFI_DEBUG("WIFI就绪\r\n");

  break;
  case SYSTEM_EVENT_STA_DISCONNECTED:


    wifi_lianjie_shibai(event);



  break;
   case SYSTEM_EVENT_STA_CONNECTED:
    WIFI_DEBUG("WIFI已连接\r\n");

   // lvgl_hint_create(lv_scr_act(),wifi_TEXT[1][system_get_Language()],200,3);


  break;

  case SYSTEM_EVENT_STA_GOT_IP:

    wifi_lianjie_chenggong(event);



    //ESP_ERROR_CHECK(esp_wifi_disconnect());
    break;
  default:
    break;
  }
  return ESP_OK;

}
#endif


static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
#if 1
    WIFI_DEBUG("消息ID:%d\r\n",event_id);

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {

      WIFI_DEBUG("连接wifi失败");
		  wifi_lianjie_shibai();
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;

        WIFI_DEBUG("wifi连接成功:%d.%d.%d.%d", IP2STR(&event->ip_info.ip));
        wifi_lianjie_chenggong(event_data);

    }else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_SCAN_DONE)
    {
      WIFI_DEBUG("扫描结束\r\n");
      wifi_scan_list_get();
    }

#endif
}

static void user_wifi_init(void)
{

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

  //nvs_get_wifi(system_data.wifi_name,system_data.wifi_password);


  sprintf(system_data.wifi_name,"Xiaomi_GSM");
  sprintf(system_data.wifi_password,"17625349864");

  wifi_lianjie(system_data.wifi_name,system_data.wifi_password,NULL);

  // sprintf(wifi_config.sta.ssid,"%s",system_data.wifi_name);
  // sprintf(wifi_config.sta.password,"%s",system_data.wifi_password);

  // memcpy(wifi_data.wifi_config.sta.ssid,system_data.wifi_name,strlen(system_data.wifi_name));
  // memcpy(wifi_data.wifi_config.sta.password,system_data.wifi_password,strlen(system_data.wifi_password));

  // WIFI_DEBUG("wifi名称:%s\r\n",wifi_data.wifi_config.sta.ssid);
  // WIFI_DEBUG("wifi密码:%s\r\n",wifi_data.wifi_config.sta.password);
  // //ESP_ERROR_CHECK(esp_wifi_disconnect());

  // WIFI_DEBUG("启动WIFI...\r\n");
  // ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  // ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_data.wifi_config));
  // ESP_ERROR_CHECK(esp_wifi_start());
 // ESP_ERROR_CHECK(esp_wifi_connect());

  ESP_ERROR_CHECK(esp_wifi_get_mac(ESP_IF_WIFI_STA,system_data.MAC));
  WIFI_DEBUG("WIFI MAC:%02x:%02x:%02x:%02x:%02x:%02x\r\n",system_data.MAC[0],system_data.MAC[1],
  system_data.MAC[2],system_data.MAC[3],system_data.MAC[4],system_data.MAC[5]);
}


int wifi_scan_list_get(void)
{

	uint16_t number = WIFI_SCAN_LIST_SIZE;			// 默认扫描列表大小
	system_data.wifi_scan_list_cnt= 0;								// 初始化AP数量0
  WIFI_DEBUG("获取wifi列表...\r\n");

	ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, system_data.wifi_ap_info));// 获取搜索的具体AP信息
	ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&system_data.wifi_scan_list_cnt));		//接入点的数量

	WIFI_DEBUG("Total APs scanned = %d\r\n",system_data.wifi_scan_list_cnt);
	for (int i = 0; (i < WIFI_SCAN_LIST_SIZE) && (i < system_data.wifi_scan_list_cnt); i++)
  {

		WIFI_DEBUG("wifi名:%s wiif信号强度:%d wifi通道 %d\r\n",
    system_data.wifi_ap_info[i].ssid,
     system_data.wifi_ap_info[i].rssi,
     system_data.wifi_ap_info[i].primary
    );
		//WIFI_DEBUG("wiif信号强度:%d ",  system_data.wifi_ap_info[i].rssi);		// 打印信号强度
		// print_auth_mode(ap_info[i].authmode);				// 打印认证方式
		// if (ap_info[i].authmode != WIFI_AUTH_WEP) {
		// 	print_cipher_type(ap_info[i].pairwise_cipher, ap_info[i].group_cipher);
		// }
		//WIFI_DEBUG("wifi通道 %d\r\n", system_data.wifi_ap_info[i].primary);
	}

  //if(system_data.wifi_scan_list_cnt)
  {
    system_data.wifi_scan_flag=false;
    esp_wifi_scan_stop();
    lvgl_ShuaXin_close();
  }

  return 0;

}

int wifi_scan_list_start(void)
{

  WIFI_DEBUG("开始扫描wifi列表\r\n");
  ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, false));	// 开始扫描WIFI(默认配置，非阻塞方式)

  return 0;
}

void wifi_init(void)
{

  user_wifi_init();

  WIFI_DEBUG("创建HTTP任务\r\n");
  xTaskCreate(https_request_by_get_task,
              "https_request_by_get_task",
              1024 * 100,
              NULL,
              configMAX_PRIORITIES,
              NULL);
}


void wifi_lianjie(char *name, char *password, void(*cb)(char * text, void *dat))
{

  wifi_data.cb=cb;

  memset(wifi_data.wifi_config.sta.ssid,0x00,sizeof(wifi_data.wifi_config.sta.ssid));
  memset(wifi_data.wifi_config.sta.password,0x00,sizeof(wifi_data.wifi_config.sta.password));

  memcpy(wifi_data.wifi_config.sta.ssid,name,strlen(name));
  memcpy(wifi_data.wifi_config.sta.password,password,strlen(password));


  WIFI_DEBUG("wifi名称:%s\r\n",wifi_data.wifi_config.sta.ssid);
  WIFI_DEBUG("wifi密码:%s\r\n",wifi_data.wifi_config.sta.password);
  //ESP_ERROR_CHECK(esp_wifi_disconnect());

  if(system_data.WIFI_Sta==wifi_yilianjie)
  {

    WIFI_DEBUG("先断开wifi连接\r\n");
    system_data.WIFI_Sta=wifi_qingqiuduankai;
    ESP_ERROR_CHECK(esp_wifi_disconnect());
    while(system_data.WIFI_Sta!=wifi_yiduankai)
    {

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    WIFI_DEBUG("已断开\r\n");
  }

  WIFI_DEBUG("连接WIFI...\r\n");
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_data.wifi_config));
  ESP_ERROR_CHECK(esp_wifi_start());
  ESP_ERROR_CHECK(esp_wifi_connect());


  system_data.WIFI_Sta = wifi_lianjiehzong;

}

void wifi_lianjie_chenggong(void * event_data)
{

    WIFI_DEBUG("WIFI已获取IP\r\n");
#if 1
    ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
    WIFI_DEBUG("IP:%d.%d.%d.%d",IP2STR(&event->ip_info.ip));

    sprintf(system_data.ip,"%d.%d.%d.%d",IP2STR(&event->ip_info.ip));

    // inaddr = &event->event_info.got_ip.ip_info.netmask;
    // str = inet_ntoa(*inaddr);
    // WIFI_DEBUG( "子网掩码: %s", str);

    // sprintf(system_data.ziwangyanma,"%s",str);

    // inaddr = &event->event_info.got_ip.ip_info.gw;
    // str = inet_ntoa(*inaddr);
    // WIFI_DEBUG( "默认网关: %s", str);

    // sprintf(system_data.wangguan,"%s",str);
#endif


    sprintf(wifi_data.buf,"%s %s %s",wifi_TEXT[1][system_get_Language()],system_data.wifi_name,system_data.ip);
    lvgl_hint_create(lv_scr_act(),wifi_data.buf,200,20);


    system_data.WIFI_Sta = wifi_yilianjie;


    memcpy(system_data.wifi_name,wifi_data.wifi_config.sta.ssid,sizeof(wifi_data.wifi_config.sta.ssid));
    memcpy(system_data.wifi_password,wifi_data.wifi_config.sta.password,sizeof(wifi_data.wifi_config.sta.password));

    //nvs_set_wifi(system_data.wifi_name,system_data.wifi_password);

    system_data.HuoQu_ShiJian_Flag=true;//同步一次时间
    xSemaphoreGive(system_data.https_request_Semaphore);//释放信号量

    //start_webserver();

    if(wifi_data.cb!=NULL)
    {
      wifi_data.cb(NULL,&system_data.WIFI_Sta);
    }
}
void wifi_lianjie_shibai(void)
{
    WIFI_DEBUG("WIFI已断开\r\n");

    stop_webserver();
    //WIFI_DEBUG("启动重连\r\n");
    //ESP_ERROR_CHECK(esp_wifi_connect());

  if(system_data.WIFI_Sta==wifi_qingqiuduankai)
  {
    system_data.WIFI_Sta = wifi_yiduankai;
    lvgl_hint_create(lv_scr_act(),wifi_TEXT[2][system_get_Language()],200,3);
  }else
  {
    system_data.WIFI_Sta = wifi_lianjieshibai;

    lvgl_hint_create(lv_scr_act(),wifi_TEXT[3][system_get_Language()],200,3);

    if(wifi_data.cb!=NULL)
    {
      wifi_data.cb(NULL,&system_data.WIFI_Sta);
    }
  }
}
