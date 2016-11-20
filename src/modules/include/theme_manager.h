/**
* @file theme_manager.h
* @author vgonisanz
* @date 2016/05/31
* @brief This file a executable to test before use in pebble app
*/

#ifndef VGONI_THEME_MANAGER_H
#define VGONI_THEME_MANAGER_H

/**********
* Defines *
**********/
#define MAX_NAME_SIZE 256

/***********************************
* Variables declaration   *
************************************/
typedef struct theme_data_init
{
  char name[MAX_NAME_SIZE];
} Theme_data_init;

/**************************
* Function declarations  *
**************************/
/**
 * @brief Call first to init the manager table.
 * @description Initialize internal memory, and add all patterns to process
 */
void init_theme_manager(Theme_data_init data[], int lenght);

/**
 * @brief Call to deinit after use.
 * @description Free memory and stuffs
 */
void deinit_theme_manager();

/**
 * @brief Load a theme.
 * @description Use index in table to eme
 */
void load_theme(int index);

/**
 * @brief Unload a theme is is active.
 * @description Nothing if no is loaded a theme
 */
void unload_theme(int index);

/**
 * @brief Print theme names
 */
void print_themes_in_table();

/**
 * @brief Print current theme
 */
void print_current_theme_index();

/**********************************
* Internal Function declarations  *
***********************************/

/**
 * @brief Add a new theme
 * @description Providing data using theme_data_init
 * @param[in] data = Theme data to initialize
 */
static void add_theme_data_struct(Theme_data_init data);

/**
 * @brief Remove all theme
 */
static void remove_all_theme_data_struct();

#endif /* VGONI_THEME_MANAGER_H */
