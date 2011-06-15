#include"fvp_watch_dog.h"
#include"fvp_common.h"
#include"fvp_util.h"

struct _FvpWatchDog
{
	ArrayList *monitor_list;
	fvp_mutex_t monitor_list_lock;	
};


static void *feed_dog_thread_entry(void *para)
{
	return_val_if_failed(para != NULL, NULL);

	FvpWatchDog *thiz = (FvpWatchDog *)para;
	ArrayList *monitor_list = NULL;
	int monitor_nums = 0;
	int i = 0;
	FvpMonitor *monitor = NULL;
	
	
	while(1)
	{
		monitor_list= thiz->monitor_list;
		fvp_mutex_lock(thiz->monitor_list_lock);
		monitor_nums = array_list_get_size(monitor_list);
		
		for(i = 0; i < monitor_nums; i++)
		{
			monitor = (FvpMonitor *)array_list_get_data_by_id(monitor_list, i);
			monitor->handle(monitor);
		}
		fvp_mutex_unlock(thiz->monitor_list_lock);
		
		hi_api_wdt_feed_wdt();
		
		sleep(1);
	}

	msg_dbg("it must can't run to here fun(%s) \n", __func__);	
	
	return NULL;
}

FvpWatchDog *fvp_watch_dog_create()
{	
	FvpWatchDog *thiz = NULL;

	thiz = (FvpWatchDog *)COMM_ALLOC(sizeof(FvpWatchDog));
	if(thiz == NULL)
	{
		msg_dbg("Fun(%s) error : not enough memory\n", __func__);
		return NULL;
	}
	
	thiz->monitor_list = array_list_create();
	fvp_mutex_init(thiz->monitor_list);

	fvp_create_normal_thread(feed_dog_thread_entry, (void *)thiz, NULL);
	
	return thiz;
}		

int fvp_watch_dog_add_monitor(FvpWatchDog *thiz, FvpMonitor *monitor)
{
	return_val_if_failed(thiz != NULL && monitor != NULL, -1);

	
	fvp_mutex_lock(thiz->monitor_list_lock);

	array_list_add(thiz->monitor_list, (void *)monitor);

	fvp_mutex_unlock(thiz->monitor_list_lock);

	return 0;
}

int fvp_watch_dog_remove_monitor(FvpWatchDog *thiz, FvpMonitor *monitor)
{
	return_val_if_failed(thiz != NULL && monitor != NULL, -1);

	fvp_mutex_lock(thiz->monitor_list_lock);	
	array_list_remove(thiz->monitor_list, (void *)monitor, sizeof(FvpMonitor));
	fvp_mutex_unlock(thiz->monitor_list_lock);

	return 0;
}

void fvp_watch_dog_destroy(FvpWatchDog *thiz)
{
	if(thiz)
	{
		fvp_mutex_destroy(&thiz->monitor_list_lock);
		
		array_list_destroy(thiz->monitor_list);

		COMM_FREE(thiz);
	}
	
	return ;
}


