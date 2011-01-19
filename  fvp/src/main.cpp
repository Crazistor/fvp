#include <QApplication>
#include "configdialog.h"
#include "controller.h"
#include "fvp_globals.h"
#include "parameter.h"

int main(int argc, char *argv[])
{
	Controller *controller = NULL;
	Cores *cores = NULL;
	SetupParameter *setup_parameter = NULL;

	controller = controller_create();
	fvp_set_controller(controller);
	
	cores = cores_create();
	cores_init(cores);
	controller_bind_cores(controller, cores);
	
	setup_parameter = (SetupParameter *)COMM_ZALLOC(sizeof(SetupParameter));
	memcpy(setup_parameter,  cores_get_parameter(cores), sizeof(setup_parameter));
	fvp_set_setup_parameter(setup_parameter);

    Q_INIT_RESOURCE(configdialog);

    QApplication app(argc, argv);
    ConfigDialog dialog;

    return dialog.exec();
}

