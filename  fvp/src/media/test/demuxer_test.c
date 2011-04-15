#include"demuxer.h"
#include<assert.h>



int main(int argc, char *argv[])
{
	Demuxer *thiz = demuxer_create();
	assert(thiz != NULL);
	
	while(getchar() != 'q')
	{
		demuxer_demux(thiz);
	}

	demuxer_destroy(thiz);

	return 0;
}
