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
enum clock_configuration
{
  CLK_NORMAL_CONFIGURATION = 0,
  CLK_SIMPLE_CONFIGURATION = 1,
};

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
void clock_window_create(enum clock_configuration);
/**
 * @brief Destroy window.
 * @description Initialize internal memory, window, and add all patterns to process
 */
void clock_window_destroy();

#endif /* VGONI_CLOCK_WINDOW_H */
