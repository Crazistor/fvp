#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<stdio.h>
#include<stdlib.h>
#include"controller.h"
#include"cores.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _Controller;
typedef struct _Controller Controller;

Controller *controller_create();

int controller_bind_cores(Controller *thiz, Cores *cores);
int controller_save_parameter(Controller *thiz, SetupParameter *setup_para);

void controller_destroy(Controller *thiz);

#ifdef __cplusplus
}
#endif

#endif /*CONTROLLER_H*/
