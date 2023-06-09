#include "drv_sysclk.h"

void rcc_init_72m(){
	
	RCC_HSEConfig(RCC_HSE_ON); 
	
	while(SUCCESS != RCC_WaitForHSEStartUp());
	
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
	
	RCC_PLLCmd(ENABLE);
	
	while(SET!=RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	
	RCC_PCLK1Config(RCC_HCLK_Div2);
	
	RCC_PCLK2Config(RCC_HCLK_Div1);
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
	while(0x08 != RCC_GetSYSCLKSource());
}

