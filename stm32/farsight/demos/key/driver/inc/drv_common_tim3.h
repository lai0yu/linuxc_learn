#ifndef __DRV_COMMON_TIM3_H__
#define __DRV_COMMON_TIM3_H__

#include "stm32f10x.h"

extern void common_tim3_config(void);
extern void set_tim3_compare_value(uint8_t R, uint8_t G, uint8_t B);

#endif
