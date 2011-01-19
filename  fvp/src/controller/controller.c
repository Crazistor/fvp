#include<stddef.h>
#include"controller.h"
#include"fvp_common.h"
#include"cores.h"


struct _Controller
{
	Cores *cores;

};

#define DECL_CORES(thiz, cores) Cores *cores = (thiz != NULL)? thiz->cores:NULL

Controller *controller_create()
{
	Controller *thiz = NULL;
	thiz = (Controller *)COMM_ZALLOC(sizeof(Controller));	

	return thiz;
}

/*
 * bind cores model to the controller
 */
int controller_bind_cores(Controller *thiz, Cores *cores)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);

	thiz->cores = cores;

	return RET_OK;
}


int controller_save_parameter(Controller *thiz, SetupParameter *setup_para)
{
	return_val_if_failed(thiz != NULL, RET_INVALID_PARAMETER);
//	printf("fun(%s) :1111111111111111111111111111!\n", __func__);

	DECL_CORES(thiz, cores);
//	printf("fun(%s) :2222222222222222222222222222!\n", __func__);
	return cores_save_parameter(cores, setup_para);
}

void controller_destroy(Controller *thiz)
{
	if(thiz)
	{
			
	}
	return;
}


