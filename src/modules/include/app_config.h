/**
* @file app_config.h
* @author vgonisanz
* @date 2016/05/31
* @brief This file Hold all structures to configure app
*/

#ifndef VGONI_APPCONFIG_WINDOW_H
#define VGONI_APPCONFIG_WINDOW_H

/* Time configuration */
typedef struct time_config
{
  int show_clock;

  GRect timeRect;
  GColor timeTextShadow;
  GColor timeTextColor;
  GTextOverflowMode timeOverflow;
  GTextAlignment timeAlignment;
  GTextAttributes* timeAttributes;
  int timeInitialOffsetX;
  int timeInitialOffsetY;
  int timeSpaceOffsetX;
  int timeBigSpaceOffsetX;
  int timeShadowOffsetX;
  int timeShadowOffsetY;

} Time_config;

typedef struct character_config
{
  int show_character;

  GRect initialRect;
  GRect finalRect;

} Character_config;
/* ALL configuration ALL */
typedef struct clock_window_config
{
  Time_config time_config;
  Character_config character_config;

  int block_size;
  GRect block_rect;

} Clock_window_config;

#endif /* VGONI_APPCONFIG_WINDOW_H */
