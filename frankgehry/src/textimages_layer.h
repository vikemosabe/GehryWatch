#ifndef TEXTIMAGES_LAYER_H
#define TEXTIMAGES_LAYER_H

typedef struct {
	Layer layer;
	BmpContainer half_layer;
	BmpContainer til_layer;
	BmpContainer past_layer;
	BmpContainer noon_layer;
	BmpContainer midnight_layer;
	BmpContainer oclock_layer;
} TextImagesLayer;

void textimages_layer_init(TextImagesLayer* textimages_layer);
void textimages_layer_deinit(TextImagesLayer* textimages_layer);

void textimages_layer_show_half_image(TextImagesLayer* textimages_layer, uint8_t res_id);
void textimages_layer_hide_half_image(TextImagesLayer* textimages_layer);

void textimages_layer_show_til_image(TextImagesLayer* textimages_layer, uint8_t res_id);
void textimages_layer_hide_til_image(TextImagesLayer* textimages_layer);

void textimages_layer_show_past_image(TextImagesLayer* textimages_layer, uint8_t res_id);
void textimages_layer_hide_past_image(TextImagesLayer* textimages_layer);

void textimages_layer_show_noon_image(TextImagesLayer* textimages_layer, uint8_t res_id);
void textimages_layer_hide_noon_image(TextImagesLayer* textimages_layer);

void textimages_layer_show_midnight_image(TextImagesLayer* textimages_layer, uint8_t res_id);
void textimages_layer_hide_midnight_image(TextImagesLayer* textimages_layer);

void textimages_layer_show_oclock_image(TextImagesLayer* textimages_layer, uint8_t res_id);
void textimages_layer_hide_oclock_image(TextImagesLayer* textimages_layer);

void textimages_layer_hide(Layer image_layer);
void textimages_layer_show(Layer image_layer);
#endif // TEXTIMAGES_LAYER_H