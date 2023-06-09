#include "drv_tim3_it_breath.h"

void tim3_it_breath_config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    GPIO_InitTypeDef gpioc_init_struct;
    gpioc_init_struct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
    gpioc_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioc_init_struct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &gpioc_init_struct);

    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef tim3_init_struct;
    tim3_init_struct.TIM_ClockDivision = TIM_CKD_DIV1;
    tim3_init_struct.TIM_CounterMode = TIM_CounterMode_Up;
    tim3_init_struct.TIM_Period = 255;
    tim3_init_struct.TIM_Prescaler = 1 - 1;
    TIM_TimeBaseInit(TIM3, &tim3_init_struct);

    TIM_OCInitTypeDef tim3_oc_init_struct;
    tim3_oc_init_struct.TIM_OCMode = TIM_OCMode_PWM1;
    tim3_oc_init_struct.TIM_OutputState = TIM_OutputState_Enable;
    tim3_oc_init_struct.TIM_OCPolarity = TIM_OCPolarity_Low;
    tim3_oc_init_struct.TIM_Pulse = 0;

    TIM_ARRPreloadConfig(TIM3, ENABLE);

    TIM_OC1Init(TIM3, &tim3_oc_init_struct);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM3, &tim3_oc_init_struct);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC3Init(TIM3, &tim3_oc_init_struct);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef nvic_init_struct;
    nvic_init_struct.NVIC_IRQChannel = TIM3_IRQn;
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init_struct);

    TIM_Cmd(TIM3, ENABLE);
}

void set_tim3_compare_breath_value(uint8_t R, uint8_t G, uint8_t B) {
    TIM_SetCompare1(TIM3, B);
    TIM_SetCompare2(TIM3, G);
    TIM_SetCompare3(TIM3, R);
}
