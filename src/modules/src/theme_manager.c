#include "theme_manager.h"
//#include "mock/mock.h"

#define LOG_TAG "ThemeManager"
#include "logger.h"

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
#include <pebble.h>

/***********************************
* Internal variables declaration   *
************************************/
static struct theme_data_struct
{
	char name[MAX_NAME_SIZE];
} *theme_data_table = 0;

static int theme_data_entries = 0;
static int current_theme_index = 0;
static int is_theme_loaded = 0;
static int is_init = 0;

/**********************************
*  Function definitions           *
***********************************/
void init_theme_manager(Theme_data_init data[], int lenght)
{
	LOGD("Initializing theme manager...");

	/* Load all data */
	for(int i=0; i<lenght; i++ )
	{
		add_theme_data_struct(data[i]);
	}
	is_init = 1;
	LOGD("Initialize done!");
}

void deinit_theme_manager()
{
	if(is_init)
	{
		remove_all_theme_data_struct();
		is_init = 0;
	}
	else
	{
		LOGE("Cannot remove_all_theme_data_struct, is not init");
	}
}

void load_theme(int index)
{
	if(is_theme_loaded)
	{
		unload_theme(current_theme_index);
	}
	LOGD("Loading theme: %d", index);
	//load_data();
	is_theme_loaded = 1;
	current_theme_index = index;
}

void unload_theme(int index)
{
	if(is_theme_loaded)
	{
		LOGD("Unloading theme: %d", index);
		//unload_data();
		is_theme_loaded = 0;
	}
	else
	{
		LOGE("No theme loaded!");
	}
}

void print_themes_in_table()
{
	LOGD("Existing themes:");

	for(int i=0; i<theme_data_entries; i++ )
	{
		char name[MAX_NAME_SIZE];
		strcpy(name, theme_data_table[i].name);
		LOGD("Theme %d-th: %s", i, name);
	}
}

void print_current_theme_index()
{
	LOGD("Current theme is: %d of %d", current_theme_index, theme_data_entries);
}
/**********************************
* Internal Function definitions   *
***********************************/

void add_theme_data_struct(Theme_data_init data)
{
	LOGD("Adding theme: %s at position: %d", data.name, theme_data_entries);
	theme_data_table = realloc(theme_data_table, (theme_data_entries+1)*sizeof(struct theme_data_struct));
	strcpy(theme_data_table[theme_data_entries].name, data.name);
	theme_data_entries++;
}

void remove_all_theme_data_struct()
{
	LOGD("Removing all theme data...");
	theme_data_entries = 0;
	free(theme_data_table);
	LOGD("done.");
}
