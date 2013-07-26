#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "config.h"
#include "minutes_layer.h"
#include "hours_layer.h"
#include "textimages_layer.h"


#define MY_UUID { 0x65, 0x24, 0xd3, 0x92, 0x12, 0x67, 0x4c, 0x6d, 0xb8, 0xc2, 0x51, 0xee, 0x92, 0x56, 0xa0, 0x20 }
#if (INVERTED == 1)
#define BG_COLOR GColorBlack
#define FG_COLOR GColorWhite
#else
#define BG_COLOR GColorWhite
#define FG_COLOR GColorBlack
#endif


PBL_APP_INFO(MY_UUID,
             "Frank Gehry Watch", "Abraham Westfall",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
static MinutesLayer minutes_layer;
static TextImagesLayer textimages_layer;
static HoursLayer hours_layer;

void handle_tick( AppContextRef ctx, PebbleTickEvent *t )
{
	(void) ctx;
	PblTm time = *(t->tick_time);
	if (time.tm_min != 30 && time.tm_min != 0)
	{
		//set minutes
		minutes_layer_set_time(&minutes_layer, *(&time.tm_min));
		layer_set_hidden((Layer *)&minutes_layer.layer, false);
		//hide half
		textimages_layer_hide_half_image(&textimages_layer);
		textimages_layer_hide_oclock_image(&textimages_layer);
		if (time.tm_min > 0 && time.tm_min < 30)
		{
			textimages_layer_show_past_image(&textimages_layer, PAST);
			textimages_layer_hide_til_image(&textimages_layer);
			hours_layer_set_time(&hours_layer, *(&time.tm_hour));
			layer_set_hidden((Layer *)&hours_layer.layer, false);
		}
		else
		{
			int newhours = time.tm_hour + 1;
			textimages_layer_hide_past_image(&textimages_layer);
			textimages_layer_show_til_image(&textimages_layer, TIL);
			hours_layer_set_time(&hours_layer, newhours);
			layer_set_hidden((Layer *)&hours_layer.layer, false);
		}
	}
	else if (time.tm_min == 30)
	{
		//gotta remove the digits and display the text 'half' instead
		layer_set_hidden((Layer *)&minutes_layer.layer, true);
		hours_layer_set_time(&hours_layer, *(&time.tm_hour));
		layer_set_hidden((Layer *)&hours_layer.layer, false);
		textimages_layer_show_half_image(&textimages_layer, HALF);
		textimages_layer_show_past_image(&textimages_layer, PAST);
		textimages_layer_hide_til_image(&textimages_layer);
		textimages_layer_hide_noon_image(&textimages_layer);
		textimages_layer_hide_midnight_image(&textimages_layer);
		textimages_layer_hide_oclock_image(&textimages_layer);
	}
	else if (time.tm_min == 0)
	{
		//hide all kinds of stuff
		layer_set_hidden((Layer *)&minutes_layer.layer, true);
		textimages_layer_hide_half_image(&textimages_layer);
		textimages_layer_hide_past_image(&textimages_layer);
		textimages_layer_hide_til_image(&textimages_layer);
		//show the oclock, if it's not noon or midnight
		if (time.tm_hour != 0 && time.tm_hour != 12 && time.tm_hour != 24)
		{
			//show the oclock
			textimages_layer_show_oclock_image(&textimages_layer, OCLOCK);
			textimages_layer_hide_noon_image(&textimages_layer);
			textimages_layer_hide_midnight_image(&textimages_layer);
			hours_layer_set_time(&hours_layer, *(&time.tm_hour));
			layer_set_hidden((Layer *)&hours_layer.layer, false);
		}
		else
		{
			//hide the oclock
			textimages_layer_hide_oclock_image(&textimages_layer);
			//hide the hour digits
			layer_set_hidden((Layer *)&hours_layer.layer, true);
			if (time.tm_hour == 0 || time.tm_hour == 24)
			{
				textimages_layer_show_midnight_image(&textimages_layer, MIDNIGHT);
			}
			else
			{
				textimages_layer_show_noon_image(&textimages_layer, NOON);
			}
		}
		//show the hours digits?
		//
		
	}
}
void handle_init(AppContextRef ctx) {
  (void)ctx;

	window_init(&window, "Frank Gehry");
	window_stack_push(&window, true /* Animated */);
	resource_init_current_app( &APP_RESOURCES );
	window_set_background_color(&window, BG_COLOR);

	minutes_layer_init(&minutes_layer);
	layer_add_child(&window.layer, &minutes_layer.layer);
	hours_layer_init(&hours_layer);
	layer_add_child(&window.layer, &hours_layer.layer);
	textimages_layer_init(&textimages_layer);
	layer_add_child(&window.layer, &textimages_layer.layer);
	// Set initial time.
	PblTm time;
	get_time(&time);
	PebbleTickEvent t;
	t.tick_time = &time;
	t.units_changed = SECOND_UNIT | MINUTE_UNIT | HOUR_UNIT | DAY_UNIT;
	handle_tick(ctx, &t);
	
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = 
	{
		.tick_handler = &handle_tick,
		.tick_units = MINUTE_UNIT
	}
  };
  app_event_loop(params, &handlers);
}
