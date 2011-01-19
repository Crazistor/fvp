#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"cores.h"
#include"fvp_common.h"

int main(int argc ,char *argv[])
{
	
	Cores *cores = NULL;
	cores = cores_create();	
	assert(cores!= NULL);
	
	
	cores_init(cores);	
	assert(cores_init(cores) == RET_OK);


	cores_destroy(cores);

	return 0;
}

