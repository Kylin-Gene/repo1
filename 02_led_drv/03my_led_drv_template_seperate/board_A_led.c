#include "led_resource.h"

static struct led_resource borad_A_led = 
{
	.pin = GROUP_PIN(5, 3),
};

struct led_resource *get_led_resource(void)
{
	return &borad_A_led;
}

