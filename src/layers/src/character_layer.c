#include "character_layer.h"

#define LOG_TAG "CharacterLayer"
#include "logger.h"

/***********************************
* Internal variables declaration   *
************************************/
static Character_config character_config;
static Layer *character_layer = NULL;

/* Character has 2 states, normal or animated, change it within animation */
static GBitmap *character_normal_bmp = NULL;
static GBitmap *character_animation_bmp = NULL;

static void redraw_character_callback(Layer *layer, GContext *ctx);

/**********************************
*  Function definitions           *
***********************************/

Layer* character_create(uint32_t bitmap, Character_config config)
{
	LOGD("Creating central character....");
	character_config = config;
	character_layer = layer_create(character_config.initialRect);
	layer_set_update_proc(character_layer, &redraw_character_callback);

	// Create manually bmp, need general method TODO
	if (character_normal_bmp)
	{
		gbitmap_destroy(character_normal_bmp);
	}

	character_normal_bmp = gbitmap_create_with_resource(bitmap);
	//character_animation_bmp = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MARIO_JUMP);

	// Luigi, add selector with themes! TODO
	// Structure to contain complete animation data, interchangeable with themes
		/*
	if (character_animated_bmp)
		gbitmap_destroy(character_animated_bmp);

		character_normal_bmp = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUIGI_NORMAL);
		mario_jump_bmp = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LUIGI_JUMP);
		*/

	LOGD("character layer created!");
	return character_layer;
}

void character_destroy()
{
	if (character_normal_bmp)
	{
		gbitmap_destroy(character_normal_bmp);
	}
	if (character_animation_bmp)
	{
		gbitmap_destroy(character_animation_bmp);
	}
	layer_destroy(character_layer);
}

static void redraw_character_callback(Layer *layer, GContext *ctx)
{
  //LOGD("redraw_character_callback");
  GRect destination;
  GBitmap *bmp;

  //bmp = mario_is_down ? mario_normal_bmp : mario_jump_bmp;
  bmp = character_normal_bmp;
  destination = GRect(0, 0, gbitmap_get_bounds(bmp).size.w, gbitmap_get_bounds(bmp).size.h);

  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  graphics_draw_bitmap_in_rect(ctx, bmp, destination);
}
