#include "block_layer.h"

#define LOG_TAG "BlockLayer"
#include "logger.h"

/***********************************
* Internal variables declaration   *
************************************/
static Layer *block_layer = NULL;
static GRect block_rect;
static GBitmap *block_bmp = NULL;

static void redraw_block_callback(Layer *layer, GContext *ctx);

/**********************************
*  Function definitions           *
***********************************/

Layer* block_create(uint32_t bitmap, GRect rect)
{
	LOGD("Creating block layer....");
	// Store variables and initializes
	block_rect = rect;
	block_layer = layer_create(block_rect);

	// Load bitmap
	block_bmp = gbitmap_create_with_resource(bitmap);

	// Add redraw method
	layer_set_update_proc(block_layer, &redraw_block_callback);

	LOGD("Block layer created!");
	return block_layer;
}

// Draw two block
static void redraw_block_callback(Layer *layer, GContext *ctx)
{
  //LOGD("redraw_block_callback");

  // Compose adding images
  graphics_context_set_compositing_mode(ctx, GCompOpAssign);

  // Update block image
  GRect layer_bounds = layer_get_bounds(layer);
  graphics_draw_bitmap_in_rect(ctx, block_bmp, layer_bounds);
}

void block_destroy()
{
	if (block_bmp)
	{
		gbitmap_destroy(block_bmp);
	}
	layer_destroy(block_layer);
}
