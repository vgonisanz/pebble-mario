/**
* @file clock_window.h
* @author vgonisanz
* @date 2016/05/31
* @brief This file a executable to test before use in pebble app
*/

#ifndef VGONI_CLOCK_WINDOW_H
#define VGONI_CLOCK_WINDOW_H

#include "app_config.h"

/**********
* Defines *
**********/

/***********************************
* Variables declaration   *
************************************/

/**************************
* Function declarations  *
**************************/
/**
 * @brief Create app.
 * @description Initialize internal memory, window, and add all patterns to process
 */
void clock_window_create(Clock_window_config customConfig);
/**
 * @brief Destroy window.
 * @description Initialize internal memory, window, and add all patterns to process
 */
void clock_window_destroy();
/**
 * @brief Create a template of configuration.
 * @description According type of pebble, configure using different parameters.
 * You can create your own configuration by yourself.
 * @param[out] A configuration according device
 */
Clock_window_config get_window_configuration(Cw_config_type type);

#endif /* VGONI_CLOCK_WINDOW_H */
