#include <pebble.h>
#include "pebble_config.h"

#include "strutils.h"

#include "clock.h"
#include "fonts.h"

#include "clock_window.h"

#include "background_layer.h"
#include "date_layer.h"
#include "time_layer.h"
#include "character_layer.h"
#include "block_layer.h"

#define LOG_TAG "ClockWindow"
#include "logger.h"

// Private data
static Clock_window_config config;  // TODO check if can avoid store this

static Window *window = NULL;
static Layer *window_layer = NULL;

// Declarations
static Clock_window_config get_wc_normal();
static Clock_window_config get_wc_simple();

static void create_layers();
static void destroy_layers();

/***********************************
*       Handlers                  *
************************************/
static void select_click_handler(ClickRecognizerRef recognizer, void *context);
static void up_click_handler(ClickRecognizerRef recognizer, void *context);
static void down_click_handler(ClickRecognizerRef recognizer, void *context);
static void click_config_provider(void *context);

/***********************************
*       Callbacks                  *
************************************/
// Handler to window
static void window_load_callback(Window *window);
static void window_unload_callback(Window *window);
// functions assigned to clock
static void update_second_callback();
static void update_minute_callback();

// Definitions
void clock_window_create(Clock_window_config customConfig)
{
  LOGD("Creating window...");
  config = customConfig;

  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load_callback,
    .unload = window_unload_callback,
  });
  const bool animated = true;
  window_stack_push(window, animated);
  LOGD("Done initializing, pushed window: %p", window);
}

void clock_window_destroy()
{
  LOGD("Destroying window...");
  destroy_layers();
  //unload_bitmaps_if_needed();
  window_destroy(window);
  LOGD("Windows destroyed!");
}

Clock_window_config get_window_configuration(Cw_config_type type)
{
  Clock_window_config configuration;
  switch(type)
  {
    case CW_NORMAL:
      configuration = get_wc_normal();
      break;
    case CW_SIMPLE:
      configuration = get_wc_simple();
      break;
    default:
      configuration = get_wc_normal();
      break;
  }
  return configuration;
}

/* TODO move to configuration */
#define BLOCK_SIZE 50

static void create_layers()
{
  // Variables needed
  GRect bounds = layer_get_bounds(window_layer);
  GFont font_small = get_font_small();
  GFont font_main = get_font_main();

  // Create layer pointers
  Layer* background_layer = background_create(RESOURCE_ID_IMAGE_EXAMPLE, GRect(0, 0, screen_size_x, screen_size_y));
  TextLayer* date_layer = date_create(font_small, GRect(0, 0, bounds.size.w, 20));
  Layer* block_layer = block_create(RESOURCE_ID_IMAGE_BLOCK, GRect(22 + offset_x, 25 + offset_y, BLOCK_SIZE*2, BLOCK_SIZE + 4));
  Layer* time_layer = time_create(font_main, config.time_config);
  Layer* character_layer = character_create(RESOURCE_ID_IMAGE_MARIO_NORMAL, config.character_config);

  // Add layers to structure
  layer_add_child(window_layer, background_layer);
  layer_add_child(window_layer, text_layer_get_layer(date_layer));
  layer_add_child(background_layer, block_layer);
  layer_add_child(background_layer, time_layer);
  layer_add_child(background_layer, character_layer);
}

static void destroy_layers()
{
  LOGD("Destroying all layers...");
  background_destroy();
  date_destroy();
  character_destroy();
  block_destroy();
}
/***********************************
*       Handlers                  *
************************************/
static void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
  LOGD("Select pushed");
  //text_layer_set_text(date_layer, "Select");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
  LOGD("Up pushed");
  //text_layer_set_text(date_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
  LOGD("Down pushed");
  //text_layer_set_text(date_layer, "Down");
}

static void click_config_provider(void *context)
{
  LOGD("Subscribing callbacks...");
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

/***********************************
*       Callbacks                  *
************************************/
static void update_second_callback()
{
  //LOGD("update_second_callback");

  // Redraw time
  time_set_dirty();
}
static void update_minute_callback()
{
  //LOGD("update_minute_callback");
}

static void window_load_callback(Window *window)
{
  LOGD("window_load_callback");
  // Window is create, you can now use main pointer
  window_layer = window_get_root_layer(window);
  //load_bitmaps();
  create_layers();

  // start getting callbacks
  clock_set_callback_s(update_second_callback);
  clock_set_callback_m(update_minute_callback);

  // Force redraw
  //time_set_dirty(); // No force here
}

static void window_unload_callback(Window *window)
{
  LOGD("window_unload_callback");
  clock_window_destroy(); //< Auto destroy elements
}

Clock_window_config get_wc_normal()
{
  Clock_window_config configuration;
  // BLOCK_SIZE = 50
  //GRect(0, BLOCK_SIZE + 4 + 5, BLOCK_SIZE*2, BLOCK_SIZE);

  // GRect(0, 50 + 4 + 5, 50*2, 50)
  // Time
  //configuration.timeRect = GRect(0, 50 + 4 + 5, 50*2, 50);
  configuration.time_config.timeRect = GRect(screen_size_x /2 - 50, screen_size_y/4, 100, 50);
  configuration.time_config.timeTextShadow = GColorBlack;
  configuration.time_config.timeTextColor = GColorBulgarianRose;
  configuration.time_config.timeOverflow = GTextOverflowModeTrailingEllipsis;
  configuration.time_config.timeAlignment = GTextAlignmentLeft;
  configuration.time_config.timeAttributes = NULL;
  configuration.time_config.timeInitialOffsetX = 3;
  configuration.time_config.timeInitialOffsetY = 1;
  configuration.time_config.timeSpaceOffsetX = 20;
  configuration.time_config.timeBigSpaceOffsetX = 30;
  configuration.time_config.timeShadowOffsetX = 4;
  configuration.time_config.timeShadowOffsetY = 1;

  // Character
  // GROUND_HEIGHT = 26
  configuration.character_config.initialRect = GRect(32 + 15 + offset_x, 168-26-76 + 28 + 10 + offset_y, 80, 80);
  configuration.character_config.finalRect = GRect(32 + 15 + offset_x, 50 + 4 + 10 + offset_y, 80, 80);

  return configuration;
}

Clock_window_config get_wc_simple()
{
  Clock_window_config configuration;
  // BLOCK_SIZE = 50
  //GRect(0, BLOCK_SIZE + 4 + 5, BLOCK_SIZE*2, BLOCK_SIZE);

  // GRect(0, 50 + 4 + 5, 50*2, 50)
  // Time
  //configuration.timeRect = GRect(0, 50 + 4 + 5, 50*2, 50);
  configuration.time_config.timeRect = GRect(screen_size_x /2 - 50, screen_size_y /2 - 25, 100, 50);
  configuration.time_config.timeTextShadow = GColorBlack;
  configuration.time_config.timeTextColor = GColorBulgarianRose;
  configuration.time_config.timeOverflow = GTextOverflowModeTrailingEllipsis;
  configuration.time_config.timeAlignment = GTextAlignmentLeft;
  configuration.time_config.timeAttributes = NULL;
  configuration.time_config.timeInitialOffsetX = 3;
  configuration.time_config.timeInitialOffsetY = 1;
  configuration.time_config.timeSpaceOffsetX = 20;
  configuration.time_config.timeBigSpaceOffsetX = 30;
  configuration.time_config.timeShadowOffsetX = 4;
  configuration.time_config.timeShadowOffsetY = 1;

  // Character
  // GROUND_HEIGHT = 26
  configuration.character_config.initialRect = GRect(32 + 15 + offset_x, 168-26-76 + 28 + 10 + offset_y, 80, 80);
  configuration.character_config.finalRect = GRect(32 + 15 + offset_x, 50 + 4 + 10 + offset_y, 80, 80);
  return configuration;
}
