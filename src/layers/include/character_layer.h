/**
* @file character_layer.h
* @author vgonisanz
* @date 2016/05/31
* @brief This file a executable to test before use in pebble app
*/

#ifndef VGONI_CHARACTER_LAYER_H
#define VGONI_CHARACTER_LAYER_H

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
Layer* character_create(uint32_t bitmap, Character_config config);

/**
 * @brief Call after using it!
 * @description
 */
void character_destroy();

#endif /* VGONI_CHARACTER_LAYER_H */
