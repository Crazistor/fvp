#include "controller.h"
#include "fvp_globals.h"
#include "parameter.h"
#include "framebuffer.h"
#include "fvp_gui.h"


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

	framebuffer = framebuffer_create("/dev/fb0");
	framebuffer_init(framebuffer, 1024, 768);

	init_gui(argc, argv);

    return 0;
}


