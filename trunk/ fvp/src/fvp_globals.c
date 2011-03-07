#include"fvp_globals.h"

struct _FvpGlobals
{
	Controller *controller;
	SetupParameter *setup_parameter;
	FvpScreen *vga_screen;
	FvpScreen *bnc_screen;
}g_globals;


void fvp_set_controller(Controller *controller)
{
	g_globals.controller = controller;
	return;
}


Controller *fvp_default_controller(void)
{
	return g_globals.controller;
}

void fvp_set_setup_parameter(SetupParameter *setup_parameter)
{
	g_globals.setup_parameter = setup_parameter;
	return;
}

SetupParameter *fvp_default_setup_parameter(void)
{
	return g_globals.setup_parameter;
}

void fvp_set_vag_screen(FvpScreen *vga_screen)
{
	g_globals.vga_screen = vga_screen;
	return;
}

FvpScreen *fvp_default_vga_screen(void)
{
	
	return g_globals.vga_screen;
}

void fvp_set_bnc_screen(FvpScreen *bnc_screen)
{
	g_globals.bnc_screen = bnc_screen;
	return;
}

FvpScreen *fvp_default_bnc_screen(void)
{
	return g_globals.bnc_screen;
}


