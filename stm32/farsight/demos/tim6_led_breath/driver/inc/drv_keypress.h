#ifndef __DRV_KEYPRESS_H__
#define __DRV_KEYPRESS_H__

#include "stm32f10x.h"
#include "drv_systick.h"

extern void key_config(void);
extern uint8_t is_key_press(void);

#endif
