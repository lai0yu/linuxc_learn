#include "drv_common_tim3.h"

void common_tim3_config(void) {
    // 使能TIM3和GPIOC时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    // 配置GPIO
    GPIO_InitTypeDef gpioc_init_struct;
    gpioc_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioc_init_struct.GPIO_Speed = GPIO_Speed_10MHz;
    gpioc_init_struct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
    GPIO_Init(GPIOC, &gpioc_init_struct);

    // 重映射
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

    // 配置通用定时器TIM3
    TIM_TimeBaseInitTypeDef tim3_init_struct;
    tim3_init_struct.TIM_Period = 255;
    tim3_init_struct.TIM_Prescaler = 1 - 1;
    tim3_init_struct.TIM_ClockDivision = TIM_CKD_DIV1;
    tim3_init_struct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &tim3_init_struct);

    // 配置 TIM3 通道1~3 为 PWM 模式
    TIM_OCInitTypeDef tim3_ocinit_struct;
    tim3_ocinit_struct.TIM_OCMode = TIM_OCMode_PWM1;
    tim3_ocinit_struct.TIM_OutputState = TIM_OutputState_Enable;
    tim3_ocinit_struct.TIM_Pulse = 0;
    tim3_ocinit_struct.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC1Init(TIM3, &tim3_ocinit_struct);
    TIM_OC2Init(TIM3, &tim3_ocinit_struct);
    TIM_OC3Init(TIM3, &tim3_ocinit_struct);

    // 使能预装载寄存器
    TIM_ARRPreloadConfig(TIM3, ENABLE);

    // 使能 TIM3 1~3通道
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

    // 使能 TIM3
    TIM_Cmd(TIM3, ENABLE);
}

void set_tim3_compare_value(uint8_t R, uint8_t G, uint8_t B) {
    TIM_SetCompare1(TIM3, B);
    TIM_SetCompare2(TIM3, G);
    TIM_SetCompare3(TIM3, R);
}
