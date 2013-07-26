#include "pebble_os.h"
#include "pebble_app.h"
#include "minutes_layer.h"
#include "config.h"

//Set these here in case we need to shift things a bit
#define LEFT 12
#define TOP 0
#define OFFSET 36

static uint8_t DIGIT_RESOURCES[] = {
	RESOURCE_ID_DIGIT_ZERO_BLACK,
	RESOURCE_ID_DIGIT_ONE_BLACK,
	RESOURCE_ID_DIGIT_TWO_BLACK,
	RESOURCE_ID_DIGIT_THREE_BLACK,
	RESOURCE_ID_DIGIT_FOUR_BLACK,
	RESOURCE_ID_DIGIT_FIVE_BLACK,
	RESOURCE_ID_DIGIT_SIX_BLACK,
	RESOURCE_ID_DIGIT_SEVEN_BLACK,
	RESOURCE_ID_DIGIT_EIGHT_BLACK,
	RESOURCE_ID_DIGIT_NINE_BLACK,
};
static int temp_tens, temp_ones;
static int current_tens;

void minutes_layer_set_time(MinutesLayer* minutes_layer, int mins)
{
	//PblTm time;
	//get_time(&time);
	//set the numbers here
	temp_tens = mins / 10;
	temp_ones = mins % 10;
	//tens
	if (temp_tens == 0 || (temp_tens == 5 && temp_ones != 0))//hide the leading zero
	{
		//layer_remove_from_parent(&minutes_layer->tens_layer.layer.layer);
		//bmp_deinit_container(&minutes_layer->tens_layer);
		layer_set_hidden((Layer *)&minutes_layer->tens_layer.layer, true);
	}
	else if (temp_ones != 0)
	{
		//if (temp_tens != current_tens)
		//{
			layer_set_hidden((Layer *)&minutes_layer->tens_layer.layer, false);
			if (temp_tens < 3)//show the 1 or 2
			{
				layer_remove_from_parent(&minutes_layer->tens_layer.layer.layer);
				bmp_deinit_container(&minutes_layer->tens_layer);
				
				bmp_init_container(DIGIT_RESOURCES[temp_tens], &minutes_layer->tens_layer);
				layer_set_frame(&minutes_layer->tens_layer.layer.layer, GRect(0, 0, 33, 64));
				layer_add_child(&minutes_layer->layer, &minutes_layer->tens_layer.layer.layer);
				//current_ten = temp_tens;
			}
			else if (temp_tens == 3)//gotta change it so shows counting down from 30 instead of counting up
			{
				//ought to get here only if it's 3 or 4
				layer_remove_from_parent(&minutes_layer->tens_layer.layer.layer);
				bmp_deinit_container(&minutes_layer->tens_layer);
				
				bmp_init_container(DIGIT_RESOURCES[5 - temp_tens], &minutes_layer->tens_layer);
				layer_set_frame(&minutes_layer->tens_layer.layer.layer, GRect(0, 0, 33, 64));
				layer_add_child(&minutes_layer->layer, &minutes_layer->tens_layer.layer.layer);
				//current_ten = temp_tens;
				//layer_set_hidden((Layer *)&minutes_layer->tens_layer.layer, false);
			}
			else
			{
				layer_remove_from_parent(&minutes_layer->tens_layer.layer.layer);
				bmp_deinit_container(&minutes_layer->tens_layer);
				
				bmp_init_container(DIGIT_RESOURCES[5 - temp_tens], &minutes_layer->tens_layer);
				layer_set_frame(&minutes_layer->tens_layer.layer.layer, GRect(0, 0, 33, 64));
				layer_add_child(&minutes_layer->layer, &minutes_layer->tens_layer.layer.layer);
				//current_ten = temp_tens;
				//layer_set_hidden((Layer *)&minutes_layer->tens_layer.layer, false);
			}
		//}
	}
	//ones
	if (temp_tens < 3)
	{
		layer_remove_from_parent(&minutes_layer->ones_layer.layer.layer);
		bmp_deinit_container(&minutes_layer->ones_layer);
		
		bmp_init_container(DIGIT_RESOURCES[temp_ones], &minutes_layer->ones_layer);
		layer_set_frame(&minutes_layer->ones_layer.layer.layer, GRect(OFFSET, 0, 33, 64));
		layer_add_child(&minutes_layer->layer, &minutes_layer->ones_layer.layer.layer);
		//current_one = temp_ones;
	}
	else if (temp_tens > 2)
	{
		if (temp_ones != 0)
		{
			layer_remove_from_parent(&minutes_layer->ones_layer.layer.layer);
			bmp_deinit_container(&minutes_layer->ones_layer);
			
			bmp_init_container(DIGIT_RESOURCES[10 - temp_ones], &minutes_layer->ones_layer);
			layer_set_frame(&minutes_layer->ones_layer.layer.layer, GRect(OFFSET, 0, 33, 64));
			layer_add_child(&minutes_layer->layer, &minutes_layer->ones_layer.layer.layer);
			//current_one = temp_ones;
		}
		else
		{
			layer_remove_from_parent(&minutes_layer->ones_layer.layer.layer);
			bmp_deinit_container(&minutes_layer->ones_layer);
			
			bmp_init_container(DIGIT_RESOURCES[0], &minutes_layer->ones_layer);
			layer_set_frame(&minutes_layer->ones_layer.layer.layer, GRect(OFFSET, 0, 33, 64));
			layer_add_child(&minutes_layer->layer, &minutes_layer->ones_layer.layer.layer);
			//current_one = temp_ones;
		}
	}
	//inverted or not
	if (INVERTED == 0)
	{
		bitmap_layer_set_compositing_mode(&minutes_layer->tens_layer.layer, GCompOpAssignInverted);
		bitmap_layer_set_compositing_mode(&minutes_layer->ones_layer.layer, GCompOpAssignInverted);
	}
	current_tens = temp_tens;
}
void minutes_layer_init(MinutesLayer* minutes_layer)
{
	GRect frame = GRect(LEFT, TOP, 70/*width*/, 64/*height*/);
	layer_init(&minutes_layer->layer, frame);
}

void minutes_layer_deinit(MinutesLayer* minutes_layer)
{
	//kill off the bmpcontainers
	layer_remove_from_parent(&minutes_layer->tens_layer.layer.layer);
	bmp_deinit_container(&minutes_layer->tens_layer);
	layer_remove_from_parent(&minutes_layer->ones_layer.layer.layer);
	bmp_deinit_container(&minutes_layer->ones_layer);
}
