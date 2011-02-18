#include"fvp_globals.h"

struct _FvpGlobals
{
	Controller *controller;
	SetupParameter *setup_parameter;
	FvpScreen *screen;
	
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


void fvp_set_screen(FvpScreen *screen)
{
	g_globals.screen = screen;
	return;
}

FvpScreen *fvp_default_screen(void)
{
	return g_globals.screen;
}





