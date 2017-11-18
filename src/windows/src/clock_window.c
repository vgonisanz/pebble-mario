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
#define NUMBER_OF_CONFIGURATIONS 2

static Clock_window_config configurations[NUMBER_OF_CONFIGURATIONS];
static int current_conf_index = 0;

static Window *window = NULL;
static Layer *window_layer = NULL;

// Declarations
static void initialize_configs();
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
void clock_window_create(enum clock_configuration configuration_index)
{
  LOGD("Creating window...");
  initialize_configs();
  current_conf_index = configuration_index;

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

static void initialize_configs()
{
    // Config 0 - normal configurations[CLK_NORMAL_CONFIGURATION]
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeRect = GRect(screen_size_x /2 - 50, screen_size_y/4, 100, 50);
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeTextShadow = GColorBlack;
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeTextColor = GColorBulgarianRose;
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeOverflow = GTextOverflowModeTrailingEllipsis;
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeAlignment = GTextAlignmentLeft;
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeAttributes = NULL;
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeInitialOffsetX = 3;
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeInitialOffsetY = 1;
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeSpaceOffsetX = 20;
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeBigSpaceOffsetX = 30;
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeShadowOffsetX = 4;
    configurations[CLK_NORMAL_CONFIGURATION].time_config.timeShadowOffsetY = 1;

    // Character
    // GROUND_HEIGHT = 26
    configurations[CLK_NORMAL_CONFIGURATION].character_config.initialRect = GRect(32 + 15 + offset_x, 168-26-76 + 28 + 10 + offset_y, 80, 80);
    configurations[CLK_NORMAL_CONFIGURATION].character_config.finalRect = GRect(32 + 15 + offset_x, 50 + 4 + 10 + offset_y, 80, 80);

    configurations[CLK_NORMAL_CONFIGURATION].block_size = 50;
    configurations[CLK_NORMAL_CONFIGURATION].block_rect = GRect(22 + offset_x, 32 + offset_y, configurations[CLK_NORMAL_CONFIGURATION].block_size*2, configurations[CLK_NORMAL_CONFIGURATION].block_size);

    // // Config 1 - simple configurations[CLK_SIMPLE_CONFIGURATION] TODO
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeRect = GRect(screen_size_x /2 - 50, screen_size_y /2 - 25, 100, 50);
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeTextShadow = GColorBlack;
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeTextColor = GColorBulgarianRose;
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeOverflow = GTextOverflowModeTrailingEllipsis;
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeAlignment = GTextAlignmentLeft;
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeAttributes = NULL;
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeInitialOffsetX = 3;
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeInitialOffsetY = 1;
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeSpaceOffsetX = 20;
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeBigSpaceOffsetX = 30;
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeShadowOffsetX = 4;
    // configurations[CLK_SIMPLE_CONFIGURATION].time_config.timeShadowOffsetY = 1;
    //
    // // Character
    // // GROUND_HEIGHT = 26
    // configurations[CLK_SIMPLE_CONFIGURATION].character_config.initialRect = GRect(32 + 15 + offset_x, 168-26-76 + 28 + 10 + offset_y, 80, 80);
    // configurations[CLK_SIMPLE_CONFIGURATION].character_config.finalRect = GRect(32 + 15 + offset_x, 50 + 4 + 10 + offset_y, 80, 80);
}

static void create_layers()
{
  // Variables needed
  GRect bounds = layer_get_bounds(window_layer);
  GFont font_small = get_font_small();
  GFont font_main = get_font_main();

  // Create layer pointers
  Layer* background_layer = background_create(RESOURCE_ID_IMAGE_EXAMPLE, GRect(0, 0, screen_size_x, screen_size_y));
  TextLayer* date_layer = date_create(font_small, GRect(0, 0, bounds.size.w, 20));
  Layer* block_layer = block_create(RESOURCE_ID_IMAGE_BLOCK, configurations[current_conf_index].block_rect);
  Layer* time_layer = time_create(font_main, configurations[current_conf_index].time_config);
  Layer* character_layer = character_create(RESOURCE_ID_IMAGE_MARIO_NORMAL, configurations[current_conf_index].character_config);

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
