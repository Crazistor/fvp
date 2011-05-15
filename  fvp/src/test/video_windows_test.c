#include<stdio.h>
#include<assert.h>
#include"video_windows.h"
#include"mpp_common.h"
#include"mpp_system.h"


int main(int argc, char *argv[])
{
	mpp_system_init();
	VideoWindows *thiz = NULL;
	
	thiz = video_windows_create(VO_DEV_SD,  VO_OUTPUT_PAL, 1);
	
	assert(thiz != NULL);

	printf("Press any key twice to exit!");
	getchar();
	getchar();

	video_windows_unref(thiz);
	mpp_system_deinit();
		
	return 0;
}

