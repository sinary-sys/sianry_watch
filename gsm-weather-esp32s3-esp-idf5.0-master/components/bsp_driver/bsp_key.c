#include "bsp_key.h"

#include "driver/gpio.h"

uint8_t bsp_key_read_power_gpio(void)
{
	return KEY_POWER_STA;
}


void bsp_key_init(void)
{

	//gpio_reset_pin(KEY_POWER_PIN);

	//gpio_pad_select_gpio(KEY_POWER_PIN);
	gpio_set_direction(KEY_POWER_PIN, GPIO_MODE_INPUT);


}
