#include"media_player.h"
#include<assert.h>
#include"mpp_common.h"

int main(int argc, char *argv[])
{
	int vdec_chn = 0;

	RECT_S out_rect = {	.s32X = 0,
						.s32Y = 0,
						.u32Width = 720,
						.u32Height = 576
					  };

	char *access_path = "file:./test.txt";

	
	MediaPlayer *thiz = media_player_create(vdec_chn, out_rect, access_path);
	assert(thiz != NULL);
	
	media_player_play(thiz);


	int conunt = 0;
	double postion;

	media_player_control(thiz, QUERY_GET_POSITON, &postion);
	
	do
	{
		sleep(1);
		conunt ++;
	}while(conunt < 25);

	media_player_stop(thiz);
	
	media_player_destroy(thiz);
	
	return 0;
}

