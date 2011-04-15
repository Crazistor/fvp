#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"mpp_system.h"



int main(int argc, char *argv[])
{
	int ret = -1;
	
	ret = mpp_system_init();
	assert(ret == 0);
	
	ret = mpp_system_init();

	ret = mpp_system_deinit();
	assert(ret == 0);
	
	return 0;
}
