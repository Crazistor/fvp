#include"media_player.h"
#include<assert.h>

int main(int argc, char *argv[])
{

	MediaPlayer *thiz = media_player_create();
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

