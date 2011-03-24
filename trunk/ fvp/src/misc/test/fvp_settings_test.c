
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"fvp_settings.h"
#include<string.h>

int main(int argc, char *argv[])
{
	printf("Test the fvp_settings\n");
	FvpSettings *settings = NULL;
	char group_key[128] = {0};
	int value = 0;	

	settings = fvp_settings_create("settings.ini");
	assert(settings != NULL);
	strcpy(group_key, "Alarm/IsAlarmOpen");
	value = SETTINGS_GET_INT(settings, group_key, "1");
	printf("groupAndKey(%s) value(%d)\n", group_key, value);
	
	value = SETTINGS_GET_INT(settings, "Alarm/IsGoogle", "1");
	SETTINGS_GET_INT(settings, "Record/IsRecordOn", "1");
	fvp_settings_sync(settings);
	

	fvp_settings_destroy(settings);


		
	return 0;
}
