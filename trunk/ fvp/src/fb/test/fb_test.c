#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"framebuffer.h"
#include"fvp_common.h"


int main(int argc, char *argv[])
{
	FrameBuffer *thiz  = NULL;

	thiz = framebuffer_create("/dev/fb0");
	assert(thiz != NULL);
	assert(framebuffer_init(thiz, 1024, 768) == RET_OK);

	getchar();
	framebuffer_change_alpha_value(thiz, 0x00);

	getchar();
	framebuffer_destroy(thiz);
	
	return 0;
}

