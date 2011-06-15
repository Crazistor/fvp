#include "hi_api_watchdog.h"

unsigned int enable_flag = 0;

int hi_api_wdt_open(void)
{
    if(HIDVR_HAL_WDT_Open() != 0)
    {
        printf("HIDVR_HAL_WDT_Open failed!\n");
    }

    if(hi_api_wdt_enble() != 0)
    {
        printf("when open wdt,disable wdt failed!\n");
        return -1;
    }

    return 0;
}

int hi_api_wdt_close(void)
{
   if(hi_api_wdt_disable() != 0)
   {
       printf("before close, disable failed!\n");
       return -1;
   }

   HIDVR_HAL_WDT_Close();

   return 0;
}

int hi_api_wdt_reset(void)
{
    if(enable_flag != 1)
    {
        printf("watchdog not enabled!\n");
        return -1;
    }

    /*lzz*/
    //hi_api_wdt_settimeout(1000);
	HI_S32 s32Ret = HIDVR_HAL_WDT_Reset();
    sleep(1);

    return s32Ret;
}

int hi_api_wdt_settimeout(unsigned int msec)
{
    if(enable_flag != 1)
    {
        printf("watchdog not enabled!\n");
        return -1;
    }

    printf("hi_api_wdt_settimeout(%dms)\n",msec);
    return HIDVR_HAL_WDT_SetTimeout(msec);
}


int hi_api_wdt_feed_wdt(void)
{
    if (enable_flag != 1)
    {
        printf("watchdog not enabled!\n");
        return -1;
    }

    return HIDVR_HAL_WDT_Feed();
}

int hi_api_wdt_enble(void)
{
    if (HIDVR_HAL_WDT_Enable() == 0)
    {
        enable_flag = 1;
    }
    else
    {
        printf("enable wdt failed!\n");
        return -1;
    }

    return 0;
}

int hi_api_wdt_disable(void)
{
    if (HIDVR_HAL_WDT_Disable() == 0)
    {
        enable_flag = 0;
    }
    else
    {
        printf("disable wdt failed!\n");
        return -1;
    }

    return 0;
}

