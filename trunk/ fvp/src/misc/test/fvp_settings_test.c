#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"fvp_settings.h"

int main(int argc, char *argv[])
{
	printf("Test the fvp_settings \n");
	
	
	FvpSettings *settings = NULL;
	char *string = NULL;

	settings = fvp_settings_create("settings.ini");
	assert(settings != NULL);
	
	string = fvp_settings_get_value(settings, "Alarm", "google");
	
	if(string)
	{
		printf("key(google), value(%s)\n", string);
	}
	
	fvp_settings_destroy(settings);
		
	return 0;
}
