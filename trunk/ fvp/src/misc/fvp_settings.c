/*
 * File: fvp_settings.c
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
 * q
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2011-3-22 zhoumin <dcdcmin@gmail.com> created
 *
 */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> 
#include"fvp_settings.h"
#include"fvp_common.h"
#include"ini_builder.h"
#include"ini_parser.h"
#include"fvp_mmap.h"
#include"fvp_mutex.h"


struct _GroupNode;

#define MAX_COMMENT_BUF_SIZE	128

struct _FvpSettings
{
	struct _GroupNode *group_node;
	struct _GroupNode *current_group;
	fvp_mutex_t settings_lock;	
	char *settings_file_name;
	unsigned char have_comment_flag;
	char comment_buffer[MAX_COMMENT_BUF_SIZE];
};

typedef struct _PrivInfo
{
	FvpSettings *settings;
}PrivInfo;

#define COMMENT_CHAR "#" 		/*ini file with this char show that this line is the comment line*/

struct _KeyNode
{
	char *key_string;
	char *value_string;
	char *comment;
	struct _KeyNode *next_key_node;
};	

struct _GroupNode
{
	char *group_string;
	char *comment;
	struct _GroupNode *next_group;
	struct _KeyNode *key_node;
	struct _KeyNode *cur_node;
};


static int  parse_group_and_key(char *group_and_key, char *group, char *key, int max_length)
{	
	return_val_if_fail(group_and_key && group && key && max_length >0, -1);

	char *p = NULL;
	p = strstr(group_and_key, "/");

	if(p)
	{	
		int group_length = 	p - group_and_key;
		int key_length = strlen(group_and_key)-(p-group_and_key)-1;
		
		if(group_length >= max_length || key_length >= max_length)
		{			
            printf("The  grou length is too long,so we can't handle it \n");
			return -1;
		}
		
		strncpy(group, group_and_key, group_length);	
		strncpy(key, p + 1, key_length);	
		
		return 0;
	}

	return -1;
}



static struct _KeyNode *key_node_create(FvpSettings *settings, char *key, char *value)
{
	return_val_if_fail(settings && key , NULL);
	
	struct _KeyNode *key_node = (struct _KeyNode *)COMM_ZALLOC(sizeof(*key_node));

	key_node->key_string = COMM_STRDUP(key);
	key_node->value_string = COMM_STRDUP(value);

	/*if have a comment*/
	if(settings->have_comment_flag)
	{	
		key_node->comment = COMM_STRDUP(settings->comment_buffer);
		settings->have_comment_flag = 0;
	}

	return key_node;
}

static int groupNode_add_keyNode(struct _GroupNode *group_node, struct _KeyNode *key_node)
{
	return_val_if_fail(group_node, -1);
	return_val_if_fail(key_node, -1);
	if(group_node && key_node)
	{	
	
		/*if first key_node is null add to the first keynode*/
		if(group_node->key_node == NULL)
		{	
			group_node->key_node = key_node;
			group_node->cur_node = key_node;
		}
		else
		{
		
			group_node->cur_node->next_key_node = key_node;
			group_node->cur_node = key_node;
		}
		return 0;
	}
	return -1;
}

static int fvp_settings_add_key_value(FvpSettings *settings, char *key, char *value)
{
	return_val_if_fail(settings != NULL && key != NULL, -1);

	if(settings->group_node != NULL)
	{	
		/*create a key node*/
		struct _KeyNode *key_node = key_node_create(settings, key, value);	
		return_val_if_fail(key_node != NULL, -1);
		
		/*add the key node to the last group */
		struct _GroupNode *current_group = settings->current_group;
		
		if(current_group)
		{
			return groupNode_add_keyNode(current_group, key_node);
		}
	}
	
	return -1;
}

static int fvp_settings_add_group(FvpSettings *settings, char *group)
{
	return_val_if_fail(settings != NULL && group != NULL, -1);

	/*create a group node*/
	struct _GroupNode *group_node  = (struct _GroupNode*)COMM_ZALLOC(sizeof(*group_node));
	group_node->group_string = COMM_STRDUP(group);
	group_node->key_node = NULL;
	if(settings->have_comment_flag)
	{	
		group_node->comment = COMM_STRDUP(settings->comment_buffer);
		settings->have_comment_flag = 0;
	}
	
	/*add the group to group list*/
	if(settings->group_node == NULL)
	{
		settings->group_node = group_node;
		settings->current_group = group_node;
	}
	else
	{
		settings->current_group->next_group = group_node;
		settings->current_group = group_node;
	}
	
	return 0;
}


static int fvp_settings_store_comment(FvpSettings *settings, char *comment)
{
	return_val_if_fail(settings && comment, -1);

	
	settings->have_comment_flag = 1;

	strncpy(settings->comment_buffer, comment, MAX_COMMENT_BUF_SIZE);
	
	return 0;
}
static void  fvp_settings_builder_on_group(IniBuilder *thiz, char *group)
{
	return_if_fail(thiz != NULL && group != NULL);
	
	DECL_PRIV(thiz, priv);
	
	fvp_settings_add_group(priv->settings, group);
	return;
}

static void fvp_settings_builder_on_key_value(IniBuilder *thiz, char *key, char *value)
{
	return_if_fail(thiz != NULL && key != NULL);
	
	DECL_PRIV(thiz, priv);
	
	fvp_settings_add_key_value(priv->settings, key, value);
	return;
}

static void fvp_settings_builder_on_comment(IniBuilder *thiz, char *comment)
{
	return_if_fail(thiz != NULL && comment != NULL);

	DECL_PRIV(thiz, priv);
	
	fvp_settings_store_comment(priv->settings, comment);
	
	return;
}

static void fvp_settings_builder_destroy(IniBuilder *thiz)
{
	if(thiz)
	{	
		thiz->ref_count--;
		if(thiz->ref_count <= 0)
		{
			COMM_ZFREE(thiz, sizeof(IniBuilder) + sizeof(PrivInfo));
		}
	}
}

static IniBuilder *fvp_settings_builder_create(void)
{
	IniBuilder *thiz = COMM_ZALLOC(sizeof(IniBuilder) + sizeof(PrivInfo)); 
	if(thiz != NULL)
	{
		thiz->on_group = fvp_settings_builder_on_group;
		thiz->on_key_value = fvp_settings_builder_on_key_value;
		thiz->on_comment = fvp_settings_builder_on_comment;
		thiz->destroy = fvp_settings_builder_destroy;	
		thiz->ref_count = 0;
	}

	return thiz;
}


static  int fvp_settings_parser_file(FvpSettings *thiz)
{
	return_val_if_fail(thiz != NULL && thiz->settings_file_name != NULL, -1);
	
	IniParser *parser = NULL;
	IniBuilder *builder = NULL;
	FvpMmap *ini_mmap = NULL;
	
	/*create the ini parser*/
	parser = ini_parser_create();
	ini_mmap = fvp_mmap_create(thiz->settings_file_name, 0, -1);
	if(ini_mmap == NULL)
	{
		ini_parser_destory(parser);
		return -1;
	}
	
	/*create the builder*/
	builder = fvp_settings_builder_create();
	if(builder == NULL)
	{		
		fvp_mmap_destroy(ini_mmap);
		ini_parser_destory(parser);
		return -1;
	}	
	PrivInfo* priv = (PrivInfo *)builder->priv;
	priv->settings = thiz;
	
	ini_parser_set_builder(parser, builder);
	/*parser the ini file*/
	char *data = fvp_mmap_data(ini_mmap);
	ini_parser_parse(parser, data, COMMENT_CHAR);

	/*destroy the parser and builder*/
	fvp_mmap_destroy(ini_mmap);
	ini_parser_destory(parser);
	ini_builder_destroy(builder);
	return 0;
}		

FvpSettings *fvp_settings_create(char *settings_file)
{	
	return_val_if_fail(settings_file != NULL, NULL);
	
	FvpSettings *thiz = NULL;

	thiz = (FvpSettings *)COMM_ZALLOC(sizeof(FvpSettings));
	return_val_if_fail(thiz != NULL, NULL);
	fvp_mutex_init(&thiz->settings_lock);
	thiz->settings_file_name = COMM_STRDUP(settings_file);
	
	thiz->current_group = NULL;
	thiz->group_node = NULL;
	/*parser the file*/
	fvp_settings_parser_file(thiz);

	return  thiz;
}


/*
 input para :group_and_key  just like as group/key
 return if find it then return the value 
 else return NULL
 */
char *fvp_settings_get_value(FvpSettings *thiz, char *group_and_key, char *default_value)
{
	return_val_if_fail(thiz && group_and_key, NULL);

	char group_buf[128] = {0};
	char key_buf[128]= {0};
	bool  is_find_group = false;
		
	/*parse the group_and_key */	
	if(parse_group_and_key(group_and_key,  group_buf,  key_buf, 128) != 0)
	{
		printf("hand the function(parse_group_and_key) failed!\n");
		return default_value;
	}

	fvp_mutex_lock(&thiz->settings_lock);
	struct _GroupNode *group_node = thiz->group_node;
	struct _KeyNode *key_node = NULL;
	for(;group_node != NULL; group_node = group_node->next_group)
	{	
		if(strcmp(group_node->group_string, group_buf) == 0)
		{	
		
			is_find_group = true;
			/*find the group node */
			key_node = group_node->key_node;
			for(;key_node ;key_node = key_node->next_key_node)
			{
				/*find the key node*/
				if(strcmp(key_node->key_string, key_buf) == 0)
				{
					fvp_mutex_unlock(&thiz->settings_lock);
					return key_node->value_string;
				}
			}

			/*find the group ,but not find the key, so we add the key and default_value to the group */
			struct _KeyNode *temp_key_node = (struct _KeyNode *)COMM_ZALLOC(sizeof(struct _KeyNode));
			temp_key_node->key_string = COMM_STRDUP(key_buf);
			temp_key_node->value_string = COMM_STRDUP(default_value);
			groupNode_add_keyNode(group_node, temp_key_node);
			fvp_mutex_unlock(&thiz->settings_lock);
            return  default_value;
			
		}
		
	}
    
    fvp_settings_add_group(thiz,  group_buf);
	fvp_settings_add_key_value(thiz, key_buf, default_value);
	
	fvp_mutex_unlock(&thiz->settings_lock);
	return default_value;
}


static int write_group_to_file(struct _GroupNode *group_node,  int fd)
{
	return_val_if_fail(group_node && fd >= 0,  -1);

	char  buf[512] = {0};
	
	/*if have comment write the comment to settings file*/
	if(group_node->comment)
	{
		sprintf(buf, "%s%s\r\n", COMMENT_CHAR, group_node->comment);
		write(fd, buf, strlen(buf));
	}

	if(group_node->group_string)
	{
		sprintf(buf,  "[%s]\r\n", group_node->group_string);
		write(fd, buf, strlen(buf));
	}

	return 0;
}


static write_key_node_to_file(struct _KeyNode *key_node, int fd)
{
	return_val_if_fail(key_node != NULL && fd >= 0, -1);
	
	char  buf[512] = {0};
	/*if have comment write the comment to settings file*/
	if(key_node->comment)
	{
		sprintf(buf, "%s%s\r\n", COMMENT_CHAR, key_node->comment);
		write(fd, buf, strlen(buf));
	}
	
	if(key_node->key_string && key_node->value_string)
	{
		sprintf(buf,  "%s=%s\r\n", key_node->key_string, key_node->value_string);
		write(fd, buf, strlen(buf));
	}
	
	return 0;
}

/*
 * useage: sync the setting to the settings file.
*/
int fvp_settings_sync(FvpSettings *thiz)
{
	return_val_if_fail(thiz != NULL, -1);
	fvp_mutex_lock(&thiz->settings_lock);

	int fd = -1;

	fd = open(thiz->settings_file_name,O_CREAT| O_WRONLY);

	if(fd >= 0)
	{
		/*foreach every group node*/
		struct _GroupNode *group_node = thiz->group_node;
		struct _KeyNode *key_node = NULL;
		for(;group_node != NULL; group_node = group_node->next_group)
		{
			write_group_to_file(group_node, fd);
			/*foreach every key node*/
			key_node = group_node->key_node;
			for(;key_node ;key_node = key_node->next_key_node)
			{
				write_key_node_to_file(key_node, fd);
			}
		}

		write(fd, "\r\n", 2);
		
		close(fd);
		fd = -1;
	
	}

	fvp_mutex_unlock(&thiz->settings_lock);
	return 0;
}


void fvp_settings_destroy(FvpSettings *thiz)
{
	if(thiz)
	{
		COMM_FREE(thiz->settings_file_name);

		struct _GroupNode *group_node = thiz->group_node;
		struct _GroupNode *temp_group_node;
		
		for( ;group_node != NULL; )
		{
			struct _KeyNode *key_node = group_node->key_node;
			struct _KeyNode *temp_key_node = NULL;

			for( ;key_node ; )
			{
				temp_key_node = key_node;
				key_node = key_node->next_key_node;
				
				COMM_FREE(temp_key_node->key_string);
				COMM_FREE(temp_key_node->value_string);
				COMM_FREE(temp_key_node->comment);
				COMM_FREE(temp_key_node);
			}
			
			temp_group_node = group_node;
			group_node = group_node->next_group;

			COMM_FREE(temp_group_node->group_string);
			COMM_FREE(temp_group_node->comment);
			COMM_FREE(temp_group_node);
		}		
		fvp_mutex_destroy(&thiz->settings_lock);
		COMM_ZFREE(thiz, sizeof(FvpSettings));
	}	
	
	return;
}



