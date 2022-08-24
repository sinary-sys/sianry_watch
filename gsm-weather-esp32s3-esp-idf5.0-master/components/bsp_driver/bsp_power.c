#include "bsp_power.h"

#include "driver/gpio.h"
#include "main.h"

void bsp_power_on(void)
{
	gpio_set_level(IO_POWER_PIN, 1);
	gpio_set_level(IO_POWER_PIN, 1);

}
void bsp_power_off(void)
{
	gpio_set_level(IO_POWER_PIN, 0);
}

xSemaphoreHandle  bsp_power_Semaphore;

void bsp_power_send_off(void)
{
	xSemaphoreGive(bsp_power_Semaphore);//释放信号量
}


static portMUX_TYPE lock = portMUX_INITIALIZER_UNLOCKED;
// #define ENTER_CRITICAL()   portENTER_CRITICAL(&cdc_acm_lock)
// #define EXIT_CRITICAL()    portEXIT_CRITICAL(&cdc_acm_lock)
static uint8_t power_flag=0;

void bsp_power_handler(void* params)
{
	uint32_t count=0;
	uint32_t count1=0;
	while (1)
	{

		// xSemaphoreTake(bsp_power_Semaphore, portMAX_DELAY);//等待信号量

		// count = uxSemaphoreGetCount(bsp_power_Semaphore);//获取信号的值
		// bap_power_DEBUG("计数信号量的值:%d\r\n",count);
		// bap_power_DEBUG("开始关机\r\n");
		bsp_power_on();

		if(power_flag==0)
		{
			if(bsp_key_read_power_gpio()==1)
			{
				if(++count>2)
				{
					power_flag=1;
					bap_power_DEBUG("进入1");
				}
			}
		}else if(power_flag==1)
		{
			if(bsp_key_read_power_gpio()==0)
			{
				if(++count>2)
				{
					power_flag=2;
					bap_power_DEBUG("进入2");
				}
			}
		}else if(power_flag==2)
		{
			if(bsp_key_read_power_gpio()==1)
			{
				bap_power_DEBUG("关机计数:%d",count);
				if(++count>20)
				{
					lvgl_hint_create(lv_scr_act(),"松手关机",200,20);

					while(bsp_key_read_power_gpio())
					{
						vTaskDelay(pdMS_TO_TICKS(10));
					}

					vTaskDelay(pdMS_TO_TICKS(1000));
					bsp_ledc_set_duty(0);
					wifi_lianjie(system_data.wifi_name,system_data.wifi_password,NULL);

					while(1)
					{
						if(++count1>100)
						{
							esp_restart();
						}
						bsp_power_off();
						vTaskDelay(pdMS_TO_TICKS(10));
					}
				}
			}else
			{
				count=0;
			}
		}

		vTaskDelay(pdMS_TO_TICKS(100));
	}

  vTaskDelete(NULL);
}

void bsp_power_init(void)
{
	bap_power_DEBUG("开始初始化");
	//gpio_reset_pin(IO_POWER_PIN);
	gpio_set_direction(IO_POWER_PIN, GPIO_MODE_OUTPUT);
	// gpio_pullup_dis(IO_POWER_PIN);
	// gpio_pulldown_dis(IO_POWER_PIN);
	gpio_set_pull_mode(IO_POWER_PIN,GPIO_PULLUP_ONLY);
    // gpio_config_t cfg = {
    //     .pin_bit_mask = BIT64(IO_POWER_PIN),
    //     .mode = GPIO_MODE_OUTPUT,
    //     //for powersave reasons, the GPIO should not be floating, select pullup
    //     .pull_up_en = true,
    //     .pull_down_en = false,
    //     .intr_type = GPIO_INTR_DISABLE,
    // };
	// gpio_config(&cfg);

	bsp_power_on();

	if(bsp_key_read_power_gpio()==0)
	{
		power_flag=2;
		bap_power_DEBUG("USB供电开机");
	}else
	{
		power_flag=0;
		bap_power_DEBUG("按键电池开机");
	}

	bsp_power_Semaphore = xSemaphoreCreateCounting(10,0);//动态创建一个计数型信号量
	xTaskCreate(bsp_power_handler, "bsp_power_handler", 1024*10, NULL, 4, NULL);

	bap_power_DEBUG("初始化结束");
}
void bsp_power_off_task_start(void)
{
	// bsp_power_Semaphore = xSemaphoreCreateCounting(10,0);//动态创建一个计数型信号量
	// xTaskCreate(bsp_power_handler, "bsp_power_handler", 1024*4, NULL, 4, NULL);
}
