#include"access_avi.h"
#include<assert.h>


#define AVI_FILENAME "file:./test.avi"

int main(int argc, char *argv[])
{
	msg_dbg("Test the avi file\n");
	Access *access_avi = NULL;
		
	access_avi = access_avi_create(AVI_FILENAME);
	assert(access_avi != NULL);

	while(getchar() != 'q')
	{
		access_block(access_avi);
	}

	access_destroy(access_avi);

	return  0;
}

