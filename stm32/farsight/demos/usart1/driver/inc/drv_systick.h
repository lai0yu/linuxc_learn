#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#define MSYSTICK_ADDR 0xE000E010
#define MSYSTICK_CTRL (*(volatile unsigned int *)(MSYSTICK_ADDR + 0x00))
#define MSYSTICK_LOAD (*(volatile unsigned int *)(MSYSTICK_ADDR + 0x04))

extern void systick_config(unsigned char i);
extern void systick_delay_ms(unsigned int i);
extern void systick_delay_us(unsigned int i);
#endif
