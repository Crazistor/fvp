#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"fvp_api_watchdog.h"


int main(int argc, char *argv[])
{
	TEST_BEGIN("test watch dog");	
	
	fvp_api_wdt_open();
	
	fvp_api_wdt_settimeout(100000);

	char ch;
	int count = 0;

	printf("usage:  a --- feed dog 10 times\n"
		   		   "r --- reboot the system\n"
		   		   "q --- quit\n");

	ch = getchar();
	if(ch == 'a')
	{
		while(1)
		{		
			if(count++ >= 10)
			{
				break;
			}
			printf("feed the watch dog count(%d)\n", count);
			fvp_api_wdt_feed_wdt();
		
			sleep(1);
		}

	}
	else if(ch == 'r')
	{
		fvp_api_wdt_reboot();
	}
	
	fvp_api_wdt_close();

	TEST_END("test watch dog");	
	return 0;
}
