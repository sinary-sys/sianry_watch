#ifndef __lvgl_RiLi_anim_H__
#define __lvgl_RiLi_anim_H__

#include "lvgl.h"
#include "lvgl_Project.h"

#if 1 
#define lvgl_RiLi_anim_DEBUG(format, ...) lvgl_project_debug("[日历-动效]- ",format,##__VA_ARGS__);
#else
#define lvgl_RiLi_anim_DEBUG(format, ...) ;
#endif


void lvgl_RiLi_anim_Jin(void);
void lvgl_RiLi_anim_Chu(void);


#endif


