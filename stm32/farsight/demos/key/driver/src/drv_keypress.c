#include "drv_keypress.h"

void key_config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;
    gpio_init_struct.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &gpio_init_struct);

    systick_config(72);
}

uint8_t is_key_press(void) {
    uint8_t is_press = 0;
    if (0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
        systick_delay_ms(50);
        if (0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            while (0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {}
            is_press = 1;
        }
    }
    return is_press;
}
