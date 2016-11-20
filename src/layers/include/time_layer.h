/**
* @file time_layer.h
* @author vgonisanz
* @date 2016/05/31
* @brief This file a executable to test before use in pebble app
*/

#ifndef VGONI_TIME_LAYER_H
#define VGONI_TIME_LAYER_H

#include <pebble.h>
#include "app_config.h"

/**********
* Defines *
**********/
// None

/***********************************
* Variables declaration   *
************************************/
// None

/**************************
* Function declarations  *
**************************/
/**
 * @brief Call first
 * @description
 * @retval Layer to add to another one or window
 */
Layer* time_create(GFont font, Time_config config);

/**
 * @brief Call after using it!
 * @description
 */
void time_destroy();
/**
 * @brief Call if want update manually time
 * @description
 */
void time_set_dirty();

#endif /* VGONI_TIME_LAYER_H */
