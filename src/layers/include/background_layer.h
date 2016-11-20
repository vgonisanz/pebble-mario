/**
* @file background_layer.h
* @author vgonisanz
* @date 2016/05/31
* @brief This file a executable to test before use in pebble app
*/

#ifndef VGONI_BACKGROUND_LAYER_H
#define VGONI_BACKGROUND_LAYER_H

#include <pebble.h>

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
Layer* background_create(uint32_t bitmap, GRect rect);

/**
 * @brief Call after using it!
 * @description
 */
void background_destroy();

#endif /* VGONI_BACKGROUND_LAYER_H */
