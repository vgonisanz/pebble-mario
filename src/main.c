// Copyright (C) 2016 Victor Goñi Sanz
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
// You may contact the author of the original watchface at denis@ddenis.info
// Author of the color mod for Pebble Time: clusterrr@clusterrr.com
//

#include <pebble.h>

#define LOG_TAG "MYMARIO"
#include "logger.h"

#include "clock.h"
#include "fonts.h"
#include "theme_manager.h"

#include "clock_window.h"

#define NUMBER_OF_THEMES 3

static void init(void)
{
  // Preview
  Theme_data_init themes[NUMBER_OF_THEMES] =
  {
    { "theme0" },
    { "theme1" },
    { "theme2" }
  };
  //init_theme_manager(themes, NUMBER_OF_THEMES);

  // Init combo
  clock_init(SECOND_UNIT);
  load_fonts();
  clock_window_create(CLK_NORMAL_CONFIGURATION);
}

static void deinit(void)
{
  // Destroy combo
  clock_deinit();
  unload_fonts();
}

int main(void)
{
  init();
  app_event_loop();
  deinit();
}
