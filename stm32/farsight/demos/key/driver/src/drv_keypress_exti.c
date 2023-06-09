#include "drv_keypress_exti.h"

void drv_keypress_it_config(void) {
    GPIO_InitTypeDef gpio_init_struct;
    EXTI_InitTypeDef exti_init_struct;
    NVIC_InitTypeDef nvic_init_struct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    gpio_init_struct.GPIO_Pin = GPIO_Pin_0;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &gpio_init_struct);

    exti_init_struct.EXTI_Line = EXTI_Line0;
    exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init_struct.EXTI_Trigger = EXTI_Trigger_Falling;
    exti_init_struct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti_init_struct);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    nvic_init_struct.NVIC_IRQChannel = EXTI0_IRQn;
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init_struct);
}
