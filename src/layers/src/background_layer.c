#include "background_layer.h"
#include "date_layer.h"

#define LOG_TAG "BackgroundLayer"
#include "logger.h"

/***********************************
* Internal variables declaration   *
************************************/
static Layer *background_layer = NULL;
static GRect background_rect;
static GBitmap *background_day_bmp = NULL;

static void redraw_background_callback(Layer *layer, GContext *ctx);

/**********************************
*  Function definitions           *
***********************************/

Layer* background_create(uint32_t bitmap, GRect rect)
{
	LOGD("Creating background layer....");
	// Store variables and initializes
	background_rect = rect;
	background_layer = layer_create(background_rect);

	// Load bitmap
	background_day_bmp = gbitmap_create_with_resource(bitmap);

	// Add redraw method
	layer_set_update_proc(background_layer, &redraw_background_callback);

	LOGD("Background layer created!");
	return background_layer;
}


// Draw background and date
// TODO check how compose battery and all kind of things
static void redraw_background_callback(Layer *layer, GContext *ctx)
{
  //LOGD("redraw_background_callback");

  // Compose adding images
  graphics_context_set_compositing_mode(ctx, GCompOpAssign);

  // Update background image
  GRect layer_bounds = layer_get_bounds(layer);
  graphics_draw_bitmap_in_rect(ctx, background_day_bmp, layer_bounds);

	// Update date layer manually because is a text layer, maybe better if it would be another type
	date_update();
}

void background_destroy()
{
	if (background_day_bmp)
	{
		gbitmap_destroy(background_day_bmp);
	}
	layer_destroy(background_layer);
}
