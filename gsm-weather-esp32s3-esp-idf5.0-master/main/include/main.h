#ifndef __main__h
#define __main__h

#include "stdint.h"
#include <stdio.h>
#include <math.h>
#include <os.h>
#include "nvs_flash.h"
#include "esp_spi_flash.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_err.h"
#include <esp_log.h>
#include <arpa/inet.h>
#include "esp_wifi.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"
#include "cJSON.h"
#include "esp_timer.h"
#include "esp_event.h"
#include "driver/ledc.h"
#include "esp_spiffs.h"


#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"


#include "nvs.h"
#include "my_spiffs.h"
#include "lvgl.h"
#include "lvgl_port.h"
#include "my_system.h"
#include "system_config_data.h"
#include "mynvs.h"


#include "cst816t.h"
#include "wifi.h"
#include "multi_button_task.h"
#include "multi_button_callback.h"
#include "lcd.h"
#include "lv_port_fs.h"
#include "bsp_i2c.h"
#include "bsp_sd.h"
#include "bsp_key.h"
#include "bsp_ledc.h"
#include "bsp_power.h"

#include "webserver.h"

#include "https_laohuangli.h"
#include "https_shijian.h"
#include "https_tianqi.h"
#include "https_riluo.h"
#include "https_kongqi.h"
#include "https_bilibili.h"
#include "https_chengshi.h"
#include "https_ip.h"
#include "https.h"
#include "user_http_s.h"


#if 1
#define my_debug( tag, format, ... ) \
ESP_LOGW(tag," %s:%d",__FILE__, __LINE__); \
printf(format,##__VA_ARGS__);
#elif 1
#define my_debug( tag, format, ... ) \
ESP_LOGW(tag,""); \
printf(format,##__VA_ARGS__);
#else
#define my_debug( tag, format, ... ) ;
#endif


#if 1
#define main_debug(format, ...) my_debug("[main]- ",format,##__VA_ARGS__);
#else
#define main_debug(format, ...) ;
#endif

void ptintf_neicun(char *file,int len);

#define printf_memory() ptintf_neicun( __FILE__, __LINE__);

#endif
