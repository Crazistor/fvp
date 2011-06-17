#include"fvp_watch_dog_servers.h"
#include"fvp_common.h"
#include"fvp_util.h"
#include"array_list.h"
#include"fvp_mutex.h"

typedef struct _FvpWatchDogServers
{
	ArrayList *monitor_list;
	fvp_mutex_t monitor_list_lock;	
	
	pthread_t feeddog_threadid;
	
}FvpWatchDogServers;

static FvpWatchDogServers *watchdog_servers = NULL;

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


int fvp_watch_dog_servers_init(void)
{
	watchdog_servers = (FvpWatchDogServers *)COMM_ALLOC(sizeof(FvpWatchDogServers));
	if(watchdog_servers == NULL)
	{
		msg_dbg("Fun(%s) error : not enough memory\n", __func__);
		return -1;
	}
	
	watchdog_servers->monitor_list = array_list_create();
	fvp_mutex_init(&watchdog_servers->monitor_list);

	fvp_api_wdt_open();
	fvp_api_wdt_settimeout(10000);

	fvp_create_normal_thread(feed_dog_thread_entry, (void *)watchdog_servers, &watchdog_servers->feeddog_threadid);

	msg_dbg("feed dog thread id(%d)\n", watchdog_servers->feeddog_threadid);
	
	return 0;
}

int fvp_watch_dog_servers_deinit(void)
{
	if(watchdog_servers)
	{
		pthread_join(watchdog_servers->feeddog_threadid, NULL);
		
		fvp_api_wdt_close();
		
		fvp_mutex_destroy(&watchdog_servers->monitor_list_lock);
		
		array_list_destroy(watchdog_servers->monitor_list);

		COMM_FREE(watchdog_servers);
		watchdog_servers = NULL;

		return 0;
	}
	
	return  -1;
}

int fvp_watch_dog_servers_add_monitor(FvpMonitor *monitor)
{
	return_val_if_failed(watchdog_servers != NULL && monitor != NULL, -1);
	
	fvp_mutex_lock(&watchdog_servers->monitor_list_lock);
	array_list_add(watchdog_servers->monitor_list, (void *)monitor);
	fvp_mutex_unlock(&watchdog_servers->monitor_list_lock);

	return 0;
}

int fvp_watch_dog_servers_remove_monitor(FvpMonitor *monitor)
{
	return_val_if_failed(watchdog_servers != NULL && monitor != NULL, -1);

	fvp_mutex_lock(&watchdog_servers->monitor_list_lock);	
	array_list_remove(watchdog_servers->monitor_list, (void *)monitor, sizeof(FvpMonitor));
	fvp_mutex_unlock(&watchdog_servers->monitor_list_lock);

	return 0;
}



