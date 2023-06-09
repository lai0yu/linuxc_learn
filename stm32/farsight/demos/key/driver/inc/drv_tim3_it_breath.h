#ifndef __DRV_TIM3_IT_BREATH_H__
#define __DRV_TIM3_IT_BREATH_H__

#include "stm32f10x.h"

extern void tim3_it_breath_config(void);
extern void set_tim3_compare_breath_value(uint8_t R, uint8_t G, uint8_t B);

#endif
