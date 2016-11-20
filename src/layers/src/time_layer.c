#include "time_layer.h"
#include "clock.h"

#define LOG_TAG "TimeLayer"
#include "logger.h"

/***********************************
* Internal variables declaration   *
************************************/
static Time_config time_config;
static Layer *time_layer = NULL;
static GBitmap *block_bmp = NULL; // ?
static GFont time_font = NULL;

static void redraw_time_callback(Layer *layer, GContext *ctx);

/**********************************
*  Function definitions           *
***********************************/

Layer* time_create(GFont font, Time_config config)
{
	LOGD("Creating time layer....");
	time_config = config;
	time_font = font;
  time_layer = layer_create(time_config.timeRect);
  layer_set_update_proc(time_layer, &redraw_time_callback);
	LOGD("time layer created!");
	return time_layer;
}

void time_destroy()
{
	layer_destroy(time_layer);
	time_layer = NULL;
}
void time_set_dirty()
{
	if(time_layer)
	{
		layer_mark_dirty(time_layer);
	}
}

static void redraw_time_callback(Layer *layer, GContext *ctx)
{
  //LOGD("redraw_time_callback");
  GRect layer_point = layer_get_bounds(layer);
  GRect copy_layer_point = layer_point;

  char* h1 = clock_get_hour_first_digit();
  char* h2 = clock_get_hour_second_digit();
  char* m1 = clock_get_minute_first_digit();
  char* m2 = clock_get_minute_second_digit();

  // Add y position
  layer_point.origin.y += time_config.timeInitialOffsetY;

  // Draw shadow
  graphics_context_set_text_color(ctx, time_config.timeTextShadow);
  layer_point.origin.x += time_config.timeShadowOffsetX;
  layer_point.origin.y += time_config.timeShadowOffsetY;
  graphics_draw_text(ctx, h1, time_font, layer_point, time_config.timeOverflow, time_config.timeAlignment, time_config.timeAttributes);
  layer_point.origin.x += time_config.timeSpaceOffsetX;
  graphics_draw_text(ctx, h2, time_font, layer_point, time_config.timeOverflow, time_config.timeAlignment, time_config.timeAttributes);
  layer_point.origin.x += time_config.timeBigSpaceOffsetX;  // Extra space
  graphics_draw_text(ctx, m1, time_font, layer_point, time_config.timeOverflow, time_config.timeAlignment, time_config.timeAttributes);
  layer_point.origin.x += time_config.timeSpaceOffsetX;
  graphics_draw_text(ctx, m2, time_font, layer_point, time_config.timeOverflow, time_config.timeAlignment, time_config.timeAttributes);

  // Restore pointer and draw number
  layer_point = copy_layer_point;
  graphics_context_set_text_color(ctx, time_config.timeTextColor);
  layer_point.origin.x += time_config.timeInitialOffsetX;
  graphics_draw_text(ctx, h1, time_font, layer_point, time_config.timeOverflow, time_config.timeAlignment, time_config.timeAttributes);
  layer_point.origin.x += time_config.timeSpaceOffsetX;
  graphics_draw_text(ctx, h2, time_font, layer_point, time_config.timeOverflow, time_config.timeAlignment, time_config.timeAttributes);
  layer_point.origin.x += time_config.timeBigSpaceOffsetX;
  graphics_draw_text(ctx, m1, time_font, layer_point, time_config.timeOverflow, time_config.timeAlignment, time_config.timeAttributes);
  layer_point.origin.x += time_config.timeSpaceOffsetX;
  graphics_draw_text(ctx, m2, time_font, layer_point, time_config.timeOverflow, time_config.timeAlignment, time_config.timeAttributes);
}
