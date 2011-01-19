#include<stdio.h>
#include<stdlib.h>
#include"parameter.h"
#include"fvp_common.h"
#include"parameter_define.h"

int main(int argc, char *argv[])
{

	Parameter *thiz = parameter_create();
	SetupParameter *para = NULL;	

	parameter_init(thiz);
	para = parameter_get_para(thiz);
	printf("record_mode channel 1 state(%d)\n", para->record_mode.is_chn_open[1]);
	para->record_mode.is_chn_open[1] = 1;
	assert(parameter_save_para(thiz) == RET_OK);
	parameter_destroy(thiz);

	
	return 0;
}
