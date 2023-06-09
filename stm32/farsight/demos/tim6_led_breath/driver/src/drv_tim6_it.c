#include "drv_tim6_it.h"

void tim6_it_config(void) {
    TIM_TimeBaseInitTypeDef tim_init_struct;
    NVIC_InitTypeDef nvic_init_struct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    tim_init_struct.TIM_Prescaler = 7200 - 1;
    tim_init_struct.TIM_Period = 10000;
    TIM_TimeBaseInit(TIM6, &tim_init_struct);

    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

    nvic_init_struct.NVIC_IRQChannel = TIM6_IRQn;
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init_struct);

    TIM_Cmd(TIM6, ENABLE);
}
