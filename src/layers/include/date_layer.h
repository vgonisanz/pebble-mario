/**
* @file date_layer.h
* @author vgonisanz
* @date 2016/05/31
* @brief This file a executable to test before use in pebble app
*/

#ifndef VGONI_DATE_LAYER_H
#define VGONI_DATE_LAYER_H

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
TextLayer* date_create(GFont font, GRect rect);

/**
 * @brief Call to update Text.
 * @description Text layer need to call for update manually
 */
void date_update();

/**
 * @brief Call after using it!
 * @description
 */
void date_destroy();

#endif /* VGONI_DATE_LAYER_H */
