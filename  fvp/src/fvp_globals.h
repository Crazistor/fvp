#ifndef FVP_GLOBALS_H
#define FVP_GLOBALS_H

#include"controller.h"
#include"parameter_define.h"

#ifdef __cplusplus
extern "C"{
#endif


void fvp_set_controller(Controller *controller);
Controller *fvp_default_controller(void);

void fvp_set_setup_parameter(SetupParameter *setup_parameter);
SetupParameter *fvp_default_setup_parameter(void);




#ifdef __cplusplus
}
#endif

#endif
