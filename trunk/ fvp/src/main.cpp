/*
 * File: main.cpp
 * Author:  zhoumin  <dcdcmin@gmail.com>
 * Brief:   
 *
 * Copyright (c) 2010 - 2013  zhoumin <dcdcmin@gmail.com>>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2011-02-24 zhoumin <dcdcmin@gmail.com> created
 *
 */

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

	FvpScreen *vga_screen = fvp_screen_create(VR_1024x768);
	fvp_set_vag_screen(vga_screen);

	framebuffer = framebuffer_create("/dev/fb0");
	framebuffer_init(framebuffer, fvp_screen_get_width(fvp_default_vga_screen()), fvp_screen_get_height(fvp_default_vga_screen()));

	init_gui(argc, argv);

    return 0;
}


