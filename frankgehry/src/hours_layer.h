#ifndef HOURS_LAYER_H
#define HOURS_LAYER_H
	
typedef struct
{
	Layer layer;
	BmpContainer tens_layer;
	BmpContainer ones_layer;
	PblTm current_time;
} HoursLayer;
void hours_layer_set_time(HoursLayer* hours_layer, int hours);
void hours_layer_init(HoursLayer* hours_layer);
void hours_layer_deinit(HoursLayer* hours_layer);

#endif // HOURS_LAYER_H