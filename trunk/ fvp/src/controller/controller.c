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

	DECL_CORES(thiz, cores);
	
	return cores_save_parameter(cores, setup_para);
}

void controller_destroy(Controller *thiz)
{
	if(thiz)
	{
		if(thiz->cores)
		{
			cores_destroy(thiz->cores);
		}		
		
		COMM_FREE(thiz);
	}

	return;
}


