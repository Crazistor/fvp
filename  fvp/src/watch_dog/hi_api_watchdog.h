#ifndef __HI_WDT_H_
#define __HI_WDT_H_
#include <stdio.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "devhal.h"

int hi_api_wdt_open(void);
int hi_api_wdt_close(void);
int hi_api_wdt_reset(void);
int hi_api_wdt_settimeout( unsigned int msec);
int hi_api_wdt_feed_wdt(void);
int hi_api_wdt_enble(void);
int hi_api_wdt_disable(void);
#endif
