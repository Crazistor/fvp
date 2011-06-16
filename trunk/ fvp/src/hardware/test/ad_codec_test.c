#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include"ad_codec.c"


int main(int argc, char *argv[])
{
	ADCodec *ad_codec = ad_codec_create();
	assert(ad_codec != NULL);

	ad_codec_config_audio_rate(ad_codec, AUDIO_SAMPLE_RATE_8000);
	
	ad_codec_destroy(ad_codec);

	return 0;
}

