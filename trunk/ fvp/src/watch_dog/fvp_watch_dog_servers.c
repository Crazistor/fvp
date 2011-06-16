#include"fvp_watch_dog_servers.h"
#include"fvp_common.h"
#include"fvp_util.h"
#include"array_list.h"
#include"fvp_mutex.h"

struct _FvpWatchDogServers
{
	ArrayList *monitor_list;
	fvp_mutex_t monitor_list_lock;	
};


static void *feed_dog_thread_entry(void *para)
{
	return_val_if_failed(para != NULL, NULL);

	FvpWatchDogServers *thiz = (FvpWatchDogServers *)para;
	ArrayList *monitor_list = NULL;
	int monitor_nums = 0;
	int i = 0;
	FvpMonitor *monitor = NULL;
	
	while(1)
	{
		monitor_list= thiz->monitor_list;
		fvp_mutex_lock(&thiz->monitor_list_lock);
		monitor_nums = array_list_get_size(monitor_list);
		
		for(i = 0; i < monitor_nums; i++)
		{
			monitor = (FvpMonitor *)array_list_get_data_by_id(monitor_list, i);
			monitor->handle(monitor);
		}
		fvp_mutex_unlock(&thiz->monitor_list_lock);
		
		msg_dbg("feed the watch dog! monitor_nums(%d)\n", monitor_nums);
		fvp_api_wdt_feed_wdt();
		
		sleep(1);
	}

	msg_dbg("it must can't run to here fun(%s) \n", __func__);	
	
	return NULL;
}

FvpWatchDogServers *fvp_watch_dog_servers_create()
{	
	FvpWatchDogServers *thiz = NULL;

	thiz = (FvpWatchDogServers *)COMM_ALLOC(sizeof(FvpWatchDogServers));
	if(thiz == NULL)
	{
		msg_dbg("Fun(%s) error : not enough memory\n", __func__);
		return NULL;
	}
	
	thiz->monitor_list = array_list_create();
	fvp_mutex_init(&thiz->monitor_list);

	fvp_api_wdt_open();
	fvp_api_wdt_settimeout(10000);

	fvp_create_normal_thread(feed_dog_thread_entry, (void *)thiz, NULL);
	
	return thiz;
}		

int fvp_watch_dog_servers_add_monitor(FvpWatchDogServers *thiz, FvpMonitor *monitor)
{
	return_val_if_failed(thiz != NULL && monitor != NULL, -1);
	
	fvp_mutex_lock(&thiz->monitor_list_lock);
	array_list_add(thiz->monitor_list, (void *)monitor);
	fvp_mutex_unlock(&thiz->monitor_list_lock);

	return 0;
}

int fvp_watch_dog_servers_remove_monitor(FvpWatchDogServers *thiz, FvpMonitor *monitor)
{
	return_val_if_failed(thiz != NULL && monitor != NULL, -1);

	fvp_mutex_lock(&thiz->monitor_list_lock);	
	array_list_remove(thiz->monitor_list, (void *)monitor, sizeof(FvpMonitor));
	fvp_mutex_unlock(&thiz->monitor_list_lock);

	return 0;
}

void fvp_watch_dog_servers_destroy(FvpWatchDogServers *thiz)
{
	if(thiz)
	{
		fvp_api_wdt_close();
		
		fvp_mutex_destroy(&thiz->monitor_list_lock);
		
		array_list_destroy(thiz->monitor_list);

		COMM_FREE(thiz);
	}
	
	return ;
}


