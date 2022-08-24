#ifndef __bsp_power_h__
#define __bsp_power_h__

#include "stdint.h"
#include "stdio.h"

#define IO_POWER_PIN       GPIO_NUM_2

#if 1
#define bap_power_DEBUG(format, ... ) my_debug("[bsp_power]:",format,##__VA_ARGS__);
#else
#define bap_power_DEBUG(format, ...) ;
#endif

void bsp_power_init(void);
void bsp_power_on(void);
void bsp_power_off(void);
void bsp_power_send_off(void);
void bsp_power_off_task_start(void);
#endif
