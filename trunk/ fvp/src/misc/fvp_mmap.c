#include"fvp_mmap.h"
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
//#include<stdbool.h>

struct _FvpMmap
{
	int fd;
	void* data;
	size_t length;
};



int fvp_mmap_exist(const char* filename)
{
	struct stat st;
	return_val_if_failed(filename != NULL, 0);

	return stat(filename, &st) == 0;
}

FvpMmap* fvp_mmap_create(const char* filename, size_t offset, size_t size)
{
	FvpMmap* thiz = NULL;
	
	
	struct stat st;
	return_val_if_failed(filename != NULL, NULL);

	if(stat(filename, &st) != 0)
	{
		return NULL;
	}
	return_val_if_failed(offset < st.st_size, NULL);


	size = (offset + size) <= st.st_size ? size : st.st_size - offset;


	thiz = COMM_ZALLOC(sizeof(FvpMmap));
	return_val_if_failed(thiz != NULL, NULL);

	thiz->fd = open(filename, O_RDONLY);
	if(thiz->fd > 0)
	{
		thiz->length = size;
		thiz->data = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE, thiz->fd, offset);
	}

	if(thiz->data == NULL || thiz->data == MAP_FAILED)
	{
		close(thiz->fd);
		COMM_ZFREE(thiz, sizeof(*thiz));
	}
	return thiz;
}

#if 1
void* fvp_mmap_data(FvpMmap* thiz)
{
	return_val_if_failed(thiz != NULL, NULL);

	return thiz->data;
}

size_t fvp_mmap_length(FvpMmap* thiz)
{
	return_val_if_failed(thiz != NULL, 0);

	return thiz->length;
}

void fvp_mmap_destroy(FvpMmap* thiz)
{
	if(thiz != NULL)
	{
		close(thiz->fd);
		munmap(thiz->data, thiz->length);

		COMM_ZFREE(thiz, sizeof(*thiz));
	}
	return;
}
#endif 

