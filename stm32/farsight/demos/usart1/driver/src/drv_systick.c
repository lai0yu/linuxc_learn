#include "drv_systick.h"

unsigned int fu_ms; 
unsigned int fu_us; 

void systick_config(unsigned char sysclk){
	MSYSTICK_CTRL &= ~0x05;
	fu_us = sysclk/8;
	fu_ms = 1000 * fu_us;
}


void systick_delay_us(unsigned int i){
 	MSYSTICK_LOAD = fu_us * i;
	MSYSTICK_CTRL |=0x01;
	unsigned int coung_flag;
	do{
		coung_flag = MSYSTICK_CTRL;
	}while(!(coung_flag&(1<<16)));
	MSYSTICK_CTRL &=~(0x01);
}

void systick_delay_ms_single(unsigned int i){
 	MSYSTICK_LOAD = fu_ms * i;
	MSYSTICK_CTRL |=0x01;
	unsigned int coung_flag;
	do{
		coung_flag = MSYSTICK_CTRL;
	}while(!(coung_flag&(1<<16)));
	MSYSTICK_CTRL &=~(0x01);
}


void systick_delay_ms(unsigned int i){
	while(i > 1864){
		systick_delay_ms_single(1864);
		i -=1864;
	}
	systick_delay_ms_single(i);
}
