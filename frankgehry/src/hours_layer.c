#include "pebble_os.h"
#include "pebble_app.h"
#include "hours_layer.h"
#include "config.h"

//Set these here in case we need to shift things a bit
#define LEFT 74
#define TOP 80
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

void hours_layer_set_time(HoursLayer* hours_layer, int hours)
{
	//PblTm time;
	//get_time(&time);
	//set the numbers here
	
	temp_ones = hours % 10;
	if (hours > 12)
	{
		temp_tens = (hours - 12) / 10;
	}
	else
	{
		temp_tens = hours / 10;
	}
	
	//tens
	if (temp_tens == 0 || (temp_tens == 12))//hide the leading zero
	{
		layer_remove_from_parent(&hours_layer->tens_layer.layer.layer);
		bmp_deinit_container(&hours_layer->tens_layer);
	}
	else
	{
		layer_remove_from_parent(&hours_layer->tens_layer.layer.layer);
		bmp_deinit_container(&hours_layer->tens_layer);
		
		bmp_init_container(DIGIT_RESOURCES[1], &hours_layer->tens_layer);
		layer_set_frame(&hours_layer->tens_layer.layer.layer, GRect(0, 0, 33, 64));
		layer_add_child(&hours_layer->layer, &hours_layer->tens_layer.layer.layer);
	}
	//ones
	if (hours > 12)
	{
		temp_ones = (hours-12) % 10;
		layer_remove_from_parent(&hours_layer->ones_layer.layer.layer);
		bmp_deinit_container(&hours_layer->ones_layer);
		
		bmp_init_container(DIGIT_RESOURCES[temp_ones], &hours_layer->ones_layer);
		layer_set_frame(&hours_layer->ones_layer.layer.layer, GRect(OFFSET, 0, 33, 64));
		layer_add_child(&hours_layer->layer, &hours_layer->ones_layer.layer.layer);
	}
	else
	{
		layer_remove_from_parent(&hours_layer->ones_layer.layer.layer);
		bmp_deinit_container(&hours_layer->ones_layer);
		
		bmp_init_container(DIGIT_RESOURCES[temp_ones], &hours_layer->ones_layer);
		layer_set_frame(&hours_layer->ones_layer.layer.layer, GRect(OFFSET, 0, 33, 64));
		layer_add_child(&hours_layer->layer, &hours_layer->ones_layer.layer.layer);
	}
	//inverted or not
	if (INVERTED == 0)
	{
		bitmap_layer_set_compositing_mode(&hours_layer->tens_layer.layer, GCompOpAssignInverted);
		bitmap_layer_set_compositing_mode(&hours_layer->ones_layer.layer, GCompOpAssignInverted);
	}
	
}
void hours_layer_init(HoursLayer* hours_layer)
{
	GRect frame = GRect(LEFT, TOP, 70/*width*/, 64/*height*/);
	layer_init(&hours_layer->layer, frame);
}

void hours_layer_deinit(HoursLayer* hours_layer)
{
	//kill off the bmpcontainers
	layer_remove_from_parent(&hours_layer->tens_layer.layer.layer);
	bmp_deinit_container(&hours_layer->tens_layer);
	layer_remove_from_parent(&hours_layer->ones_layer.layer.layer);
	bmp_deinit_container(&hours_layer->ones_layer);
}