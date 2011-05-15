/*
 * File: access_file.c
 * Author:  zhoumin  <dcdcmin@gmail.com>
 * Brief:   
 *
 * Copyright (c) 2010 - 2013  zhoumin <dcdcmin@gmail.com>>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2011-04-07 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include"access_file.h"

#include<error.h>
typedef struct _PrivInfo
{
	unsigned int i_nb_reads;
	int fd;
	Block *block;
}PrivInfo;



/*read a block from the file*/
static Block* access_file_block(Access *thiz)
{
	DECL_PRIV(thiz, priv);	

#if 0
	int ret = 0;
	ret = read(priv->fd, priv->block->p_buffer, MAX_H264_PACKET_LEN);
	
	if(ret < 0)
	{
        switch (errno)
        {
            case EINTR:
            case EAGAIN:
                break;
            default:
				msg_dbg("Failed to read\n");
                thiz->info.b_eof = true;
                return 0;
        }
	}
	else if(ret > 0)
	{
        thiz->info.i_pos += ret;
	}
	else
	{
		/*read the file end*/
        thiz->info.b_eof = true;
	}
#else 
	int ret = 0;
	int frame_size = 0;
	char buf[12] = {0};
	ret = read(priv->fd, &frame_size, 4);
	if(ret !=  4)
	{
		printf("read frame size failed! size ret(%d)\n", ret);
		
	}
	ret = read(priv->fd, priv->block->p_buffer, frame_size);
	if(ret !=  frame_size)
	{
		printf("read frame data failed! size ret(%d)\n", ret);
		perror("read file faield!\n");
	}
	priv->block->buffer_len = frame_size;
#endif 
	return priv->block;
}

/*
 * Read: standard read on a file descriptor.
 */
static int  access_file_read(Access *thiz, uint8_t *buffer, size_t len)
{
	return_val_if_failed(thiz != NULL && buffer != NULL && len >= 0, -1);
	
	int ret = -1;
	DECL_PRIV(thiz, priv);	
	/*read a len length data to the buffer*/
	ret = read(priv->fd, buffer, len);
	
	if(ret < 0)
	{
		msg_dbg("Failed to read\n");
        switch (errno)
        {
            case EINTR:
            case EAGAIN:
                break;

            default:
				msg_dbg("Failed to read\n");
                thiz->info.b_eof = true;
                return 0;
        }
	}
	else if(ret > 0)
	{
        thiz->info.i_pos += ret;
        printf("current pos(%d)\n", thiz->info.i_pos);
	}
	else
	{
        thiz->info.b_eof = true;
	}
	
	priv->i_nb_reads++;
	
	return ret;
}


/*
 * seek the file 
 */
static void access_file_seek(Access *thiz, unsigned long pos)
{
	return_if_failed(thiz != NULL );

	DECL_PRIV(thiz, priv);	
	lseek(priv->fd, pos, SEEK_SET);
	
	return;
}


/*
 * control the file
 */
static void access_file_control(Access *thiz, int query, va_list args)
{	
	return_if_failed(thiz != NULL);
	
	msg_dbg("access_file_control\n");
	
	return;
}


/*
 * destroy the access
 */
static void access_file_destroy(Access *thiz)
{
	if(thiz)
	{
		DECL_PRIV(thiz, priv);	
		if(priv->fd >= 0)
		{
			printf("fd(%d)\n", priv->fd);
			close(priv->fd);
			priv->fd = -1;
		}
		block_destroy(priv->block);
		
		COMM_ZFREE(thiz, sizeof(*thiz) + sizeof(PrivInfo));
	}
	
	return;
}

static int parse_access_path(char *access_path, char *file_name, size_t file_name_len)
{
	return_val_if_failed(access_path != NULL && file_name != NULL, -1);

	if(strstr(access_path, ACCESS_KEY_WORKD) == 0)
	{
		msg_dbg("not math the key workd(%s)\n", ACCESS_KEY_WORKD);
		return -1;
	}

	char *p = NULL;
	p = strchr(access_path, ':');
	if(p != NULL)
	{
		strncpy(file_name, p + 1, file_name_len);
		return 0;
	}

	return -1;
}

/*
 * create access 
 * input para --access_path : such as [file:/home/file_name.mov]
 */
Access *access_file_create(char *access_path)
{
	return_val_if_failed(access_path, NULL);
	
	int fd = -1;
	char file_path[64] = {0};

	/*parse the access_path get the file name*/
	if(parse_access_path(access_path, file_path, 64) != 0)
	{
		msg_dbg("Fun(%s) error parse the access_path(%s) failed!\n", __func__, access_path);
		return NULL;
	}
	
	Access *thiz = (Access *)COMM_ZALLOC(sizeof(Access) + sizeof(PrivInfo));
	return_val_if_failed(thiz != NULL, NULL);

	msg_dbg("file_path(%s)\n", file_path);
	
	/*open the file */
	fd = open(file_path, O_RDONLY);
	if(fd <= 0)
	{
		msg_dbg("error:open the file failed!\n");
		return NULL;
	}

	thiz->seek = access_file_seek;
	thiz->read = access_file_read;
	thiz->block = access_file_block;
	thiz->control = access_file_control;
	thiz->destroy = access_file_destroy;

	DECL_PRIV(thiz, priv);
	
	priv->fd = fd;
	priv->i_nb_reads = 0;
	priv->block = block_create(MAX_H264_PACKET_LEN);
	
	return thiz;
}


