#ifndef MINUTES_LAYER_H
#define MINUTES_LAYER_H
	
typedef struct
{
	Layer layer;
	BmpContainer tens_layer;
	BmpContainer ones_layer;
	PblTm current_time;
} MinutesLayer;

void minutes_layer_set_time(MinutesLayer* minutes_layer, int mins);
void minutes_layer_init(MinutesLayer* minutes_layer);
void minutes_layer_deinit(MinutesLayer* minutes_layer);

#endif // MINUTES_LAYER_H