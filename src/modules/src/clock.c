#include "clock.h"

#define LOG_TAG "Clock"
#include "logger.h"

#include <pebble.h>
#include "strutils.h"

/***********************************
* Internal variables declaration   *
************************************/
// Processed data from tick_time
static char date_text[12];
static char hour_text[3];
static char minute_text[3];
static char second_text[3];
// Auxiliar chars to draw propertly, UTF-8 zero terminated
static char h1[2];
static char h2[2];
static char m1[2];
static char m2[2];
static char s1[2];
static char s2[2];
static clock_callback_type clock_static_callback_s = NULL;
static clock_callback_type clock_static_callback_m = NULL;

/**
 * @brief Update internal clock variables
 * @description This method is called from handle_second_tick only
 */
static void clock_update(struct tm *tick_time);

/**
 * @brief Call to Update and invoke callback
 * @description This method is assigned to timer service at init. Need set
 * clock_set_callback_* propertly or will do nothing
 */
static void handle_tick(struct tm *tick_time, TimeUnits units_changed);

/**********************************
*  Function definitions           *
***********************************/
void clock_init(TimeUnits units)
{
  LOGD("Initializing ...");
  tick_timer_service_subscribe(units, handle_tick);
  // Initialize date right now
  time_t t;
  time(&t);
  struct tm * tick_time = localtime(&t);
  clock_update(tick_time);
	LOGD("Initialize done!");
}

void clock_deinit()
{
  LOGD("DeInitializing ...");
  clock_static_callback_s = NULL;
  clock_static_callback_m = NULL;
  tick_timer_service_unsubscribe();
	LOGD("DeInitialize done!");
}

void clock_set_callback_s(clock_callback_type function)
{
  clock_static_callback_s = function;
}

void clock_set_callback_m(clock_callback_type function)
{
  clock_static_callback_m = function;
}

char* clock_get_date()
{
	return date_text;
}

char* clock_get_hour()
{
	return hour_text;
}

char* clock_get_minute()
{
	return minute_text;
}

char* clock_get_second()
{
	return second_text;
}

char* clock_get_hour_first_digit()
{
	return h1;
}
char* clock_get_hour_second_digit()
{
	return h2;
}
char* clock_get_minute_first_digit()
{
	return m1;
}
char* clock_get_minute_second_digit()
{
	return m2;
}

static void clock_update(struct tm *tick_time)
{
  char *hour_format;
  if (clock_is_24h_style())
  {
    hour_format = "%H";
  }
  else
  {
    hour_format = "%I";
  }
  // update time
  strftime(hour_text, sizeof(hour_text), hour_format, tick_time);
  strftime(minute_text, sizeof(minute_text), "%M", tick_time);
  strftime(second_text, sizeof(second_text), "%S", tick_time);

  // Update date
  strftime(date_text, sizeof(date_text), "%a, %b %d", tick_time);
	to_upcase(date_text);

  h1[0] = hour_text[0];
  h2[0] = hour_text[1];
  m1[0] = minute_text[0];
  m2[0] = minute_text[1];
  h1[1] = h2[1] = m1[1] = m2[1] = 0;  // Text must be zero terminated UTF-8 string to draw
}

static void handle_tick(struct tm *tick_time, TimeUnits units_changed)
{
  clock_update(tick_time);

  if(units_changed & MINUTE_UNIT)
  {
    if(clock_static_callback_m != NULL)
    {
      clock_static_callback_m();
    }
  }
  if(units_changed & SECOND_UNIT)
  {
    if(clock_static_callback_s != NULL)
    {
      clock_static_callback_s();
    }
  }
}
