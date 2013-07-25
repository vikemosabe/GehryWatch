#include "pebble_os.h"
#include "pebble_app.h"
#include "textimages_layer.h"
#include "config.h"

void textimages_layer_init(TextImagesLayer* textimages_layer)
{
	GRect frame = GRect(0, 0, 144, 168);//this layer has to span the entire screen basically
	layer_init(&textimages_layer->layer, frame);
}
void textimages_layer_deinit(TextImagesLayer* textimages_layer)
{
	layer_remove_from_parent(&textimages_layer->half_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->half_layer);
	layer_remove_from_parent(&textimages_layer->til_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->til_layer);
	layer_remove_from_parent(&textimages_layer->past_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->past_layer);
	layer_remove_from_parent(&textimages_layer->noon_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->noon_layer);
	layer_remove_from_parent(&textimages_layer->midnight_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->midnight_layer);
	layer_remove_from_parent(&textimages_layer->oclock_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->oclock_layer);
}
//HALF
void textimages_layer_show_half_image(TextImagesLayer* textimages_layer, uint8_t res_id)
{
	bmp_init_container(res_id, &textimages_layer->half_layer);
	layer_set_frame(&textimages_layer->half_layer.layer.layer, GRect(2, 2, 74, 60));
	layer_add_child(&textimages_layer->layer, &textimages_layer->half_layer.layer.layer);
	//inverted or not
	if (INVERTED == 0)
	{
		bitmap_layer_set_compositing_mode(&textimages_layer->half_layer.layer, GCompOpAssignInverted);
	}
}
void textimages_layer_hide_half_image(TextImagesLayer* textimages_layer)
{
	layer_remove_from_parent(&textimages_layer->half_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->half_layer);
}
//TIL
void textimages_layer_show_til_image(TextImagesLayer* textimages_layer, uint8_t res_id)
{
	bmp_init_container(res_id, &textimages_layer->til_layer);
	layer_set_frame(&textimages_layer->til_layer.layer.layer, GRect(90, 20, 46, 35));
	layer_add_child(&textimages_layer->layer, &textimages_layer->til_layer.layer.layer);
	//inverted or not
	if (INVERTED == 0)
	{
		bitmap_layer_set_compositing_mode(&textimages_layer->til_layer.layer, GCompOpAssignInverted);
	}
}
void textimages_layer_hide_til_image(TextImagesLayer* textimages_layer)
{
	layer_remove_from_parent(&textimages_layer->til_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->til_layer);
}
//PAST
void textimages_layer_show_past_image(TextImagesLayer* textimages_layer, uint8_t res_id)
{
	bmp_init_container(res_id, &textimages_layer->past_layer);
	layer_set_frame(&textimages_layer->past_layer.layer.layer, GRect(0, 59, 102, 50));
	layer_add_child(&textimages_layer->layer, &textimages_layer->past_layer.layer.layer);
	//inverted or not
	if (INVERTED == 0)
	{
		bitmap_layer_set_compositing_mode(&textimages_layer->past_layer.layer, GCompOpAssignInverted);
	}
}
void textimages_layer_hide_past_image(TextImagesLayer* textimages_layer)
{
	layer_remove_from_parent(&textimages_layer->past_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->past_layer);
}
//noon
void textimages_layer_show_noon_image(TextImagesLayer* textimages_layer, uint8_t res_id)
{
	bmp_init_container(res_id, &textimages_layer->noon_layer);
	layer_set_frame(&textimages_layer->noon_layer.layer.layer, GRect(25, 99, 85, 25));
	layer_add_child(&textimages_layer->layer, &textimages_layer->noon_layer.layer.layer);
	//inverted or not
	if (INVERTED == 0)
	{
		bitmap_layer_set_compositing_mode(&textimages_layer->noon_layer.layer, GCompOpAssignInverted);
	}
}
void textimages_layer_hide_noon_image(TextImagesLayer* textimages_layer)
{
	layer_remove_from_parent(&textimages_layer->noon_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->noon_layer);
}
//MIDNIGHT
void textimages_layer_show_midnight_image(TextImagesLayer* textimages_layer, uint8_t res_id)
{
	bmp_init_container(res_id, &textimages_layer->midnight_layer);
	layer_set_frame(&textimages_layer->midnight_layer.layer.layer, GRect(5, 99, 133, 48));
	layer_add_child(&textimages_layer->layer, &textimages_layer->midnight_layer.layer.layer);
	//inverted or not
	if (INVERTED == 0)
	{
		bitmap_layer_set_compositing_mode(&textimages_layer->midnight_layer.layer, GCompOpAssignInverted);
	}
}
void textimages_layer_hide_midnight_image(TextImagesLayer* textimages_layer)
{
	layer_remove_from_parent(&textimages_layer->midnight_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->midnight_layer);
}
//OCLOCK
void textimages_layer_show_oclock_image(TextImagesLayer* textimages_layer, uint8_t res_id)
{
	bmp_init_container(res_id, &textimages_layer->oclock_layer);
	layer_set_frame(&textimages_layer->oclock_layer.layer.layer, GRect(16, 134, 99, 35));
	layer_add_child(&textimages_layer->layer, &textimages_layer->oclock_layer.layer.layer);
	//inverted or not
	if (INVERTED == 0)
	{
		bitmap_layer_set_compositing_mode(&textimages_layer->oclock_layer.layer, GCompOpAssignInverted);
	}
}
void textimages_layer_hide_oclock_image(TextImagesLayer* textimages_layer)
{
	layer_remove_from_parent(&textimages_layer->oclock_layer.layer.layer);
	bmp_deinit_container(&textimages_layer->oclock_layer);
}