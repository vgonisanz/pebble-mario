/**
* @file clock.h
* @author vgonisanz
* @date 2016/05/31
* @brief This file contain date and time management
*/

#ifndef VGONI_CLOCK_H
#define VGONI_CLOCK_H

#include <pebble.h>

/**********
* Defines *
**********/
//#define MAX_NAME_SIZE 256

/***********************************
* Variables declaration   *
************************************/
typedef void (*clock_callback_type)(); // void pointerToFunction(void );

/**************************
* Function declarations  *
**************************/
/**
 * @brief Call first to start
 * @description Internal update variables. Can get them asyncro or set a callback
 */
void clock_init(TimeUnits units);

/**
 * @brief Unsubscribe timer and remove callbacks
 * @description
 */
void clock_deinit();

/**
 * @brief Set a function to call each second, minute, etc
 * @description If no function, is NULL and no call is made. Set to a callback_* type from outside.
 */
void clock_set_callback_s(clock_callback_type function);
void clock_set_callback_m(clock_callback_type function);

char* clock_get_date();
char* clock_get_hour();
char* clock_get_minute();
char* clock_get_second();

char* clock_get_hour_first_digit();
char* clock_get_hour_second_digit();
char* clock_get_minute_first_digit();
char* clock_get_minute_second_digit();

#endif /* VGONI_CLOCK_H */
