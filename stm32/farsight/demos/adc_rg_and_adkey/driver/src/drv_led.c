#include "drv_led.h"

void led_config(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_SetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6);
}

void led_open(LedColor color) {
    GPIO_SetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6);
    switch (color) {
    case R:
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);
        break;
    case G:
        GPIO_ResetBits(GPIOC, GPIO_Pin_7);
        break;
    case B:
        GPIO_ResetBits(GPIOC, GPIO_Pin_6);
        break;
    case W:
        GPIO_ResetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6);
        break;
    default:
        GPIO_SetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6);
        break;
    }
}

void led_close(void) {
    GPIO_SetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6);
}
