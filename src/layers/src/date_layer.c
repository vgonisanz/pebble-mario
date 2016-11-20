#include "date_layer.h"
#include "clock.h"

#define LOG_TAG "dateLayer"
#include "logger.h"

/***********************************
* Internal variables declaration   *
************************************/
static TextLayer *date_layer = NULL;
static GRect date_rect;
static GFont date_font = NULL;

static void redraw_date_callback(Layer *layer, GContext *ctx);

/**********************************
*  Function definitions           *
***********************************/

TextLayer* date_create(GFont font, GRect rect)
{
	LOGD("Creating date layer....");
	date_font = font;
	date_rect = rect;
	date_layer = text_layer_create(date_rect);
	text_layer_set_font(date_layer, date_font);
	text_layer_set_background_color(date_layer, GColorFromRGBA(0, 0, 0, 0));
	text_layer_set_text_color(date_layer, GColorWhite);
	text_layer_set_text_alignment(date_layer, GTextOverflowModeTrailingEllipsis);
	text_layer_set_text(date_layer, "DATE");
	text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
	LOGD("date layer created!");
	return date_layer;
}

void date_update()
{
	char* date_text = clock_get_date();
  text_layer_set_text(date_layer, date_text);
}
static void redraw_date_callback(Layer *layer, GContext *ctx)
{
	// redraw?
	// Text layer no need
}

void date_destroy()
{
	text_layer_destroy(date_layer);
}
