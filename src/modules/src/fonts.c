#include "fonts.h"

#define LOG_TAG "Fonts"
#include "logger.h"

/***********************************
* Internal variables declaration   *
************************************/
static GFont pixel_font = NULL;
static GFont pixel_font_small = NULL;

/**********************************
*  Function definitions           *
***********************************/
GFont get_font_main()
{
	return pixel_font;
}

GFont get_font_small()
{
	return pixel_font_small;
}

void load_fonts()
{
  LOGD("Loading fonts...");
  pixel_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GAMEGIRL_24));
	pixel_font_small = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_EMULOGIC_8));
}

void unload_fonts()
{
  fonts_unload_custom_font(pixel_font);
	fonts_unload_custom_font(pixel_font_small);
}
