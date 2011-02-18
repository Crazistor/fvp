#include "controller.h"
#include "fvp_globals.h"
#include "parameter.h"
#include "framebuffer.h"
#include "fvp_gui.h"
#include "fvp_screen.h"
#include "fvp_common.h"

int main(int argc, char *argv[])
{
	Controller *controller = NULL;
	Cores *cores = NULL;
	SetupParameter *setup_parameter = NULL;
	FrameBuffer *framebuffer = NULL;


	
	controller = controller_create();
	fvp_set_controller(controller);
	/*cores model*/
	cores = cores_create();
	cores_init(cores);
	controller_bind_cores(controller, cores);
	/*search device client model*/
	SearchDeviceClient *search_device_client = search_device_client_create();
	controller_bind_search_device_client(controller, search_device_client);

	setup_parameter = (SetupParameter *)COMM_ZALLOC(sizeof(SetupParameter));
	memcpy(setup_parameter,  cores_get_parameter(cores), sizeof(setup_parameter));
	fvp_set_setup_parameter(setup_parameter);

	FvpScreen *screen = fvp_screen_create(VR_1024x768);
	fvp_set_screen(screen);

	framebuffer = framebuffer_create("/dev/fb0");
	framebuffer_init(framebuffer, fvp_screen_get_width(fvp_default_screen()), fvp_screen_get_height(fvp_default_screen()));

	init_gui(argc, argv);

    return 0;
}


