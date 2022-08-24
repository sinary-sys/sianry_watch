#ifndef __http_web__H__
#define __http_web__H__
#include "main.h"

#include "esp_http_server.h"

#if 1
#define http_web_DEBUG(format, ...) my_debug("[http_web]-",format,##__VA_ARGS__);
#else
#define http_web_DEBUG(format, ...) ;
#endif


#endif
