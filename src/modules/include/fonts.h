/**
* @file fonts.h
* @author vgonisanz
* @date 2016/05/31
* @brief This file a executable to test before use in pebble app
*/

#ifndef VGONI_FONTS_H
#define VGONI_FONTS_H

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
 */
void load_fonts();
void unload_fonts();
GFont get_font_main();
GFont get_font_small();

#endif /* VGONI_FONTS_H */
