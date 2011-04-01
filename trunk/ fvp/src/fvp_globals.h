#ifndef FVP_GLOBALS_H
#define FVP_GLOBALS_H

#include"controller.h"
#include"parameter_define.h"
#include"fvp_screen.h"

#ifdef __cplusplus
extern "C"{
#endif


void fvp_set_controller(Controller *controller);
Controller *fvp_default_controller(void);

void fvp_set_setup_parameter(SetupParameter *setup_parameter);
SetupParameter *fvp_default_setup_parameter(void);

void fvp_set_vag_screen(FvpScreen *vga_screen);
FvpScreen *fvp_default_vga_screen(void);

void fvp_set_bnc_screen(FvpScreen *bnc_screen);
FvpScreen *fvp_default_bnc_screen(void);


#ifdef __cplusplus
}
#endif

#endif
