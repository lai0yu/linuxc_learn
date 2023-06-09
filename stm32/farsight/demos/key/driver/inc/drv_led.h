#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#include "stm32f10x.h"

typedef enum e_LedColor {
    R = 0,
    G,
    B,
    W
} LedColor;

extern void led_config(void);
extern void led_open(LedColor color);
extern void led_close(void);

#endif
