#include "drv_led_register.h"

void led_config_register(void) {
    RCC_MGPIOC |= ((unsigned int)1 << 4);

    MGPIOC_CRL &= ~((unsigned int)0xff << 24);
    MGPIOC_CRL |= ((unsigned int)0x22 << 24);

    MGPIOC_CRH &= ~0x0f;
    MGPIOC_CRH |= 0x02;

    MGPIOC_ODR |= (unsigned int)0x07 << 6;
}
void led_open_register(LedColorRigister color) {
    MGPIOC_ODR |= 0x07 << 6;
    switch (color) {
    case R: MGPIOC_ODR &= ~((unsigned int)0x04 << 6); break;
    case G: MGPIOC_ODR &= ~((unsigned int)0x02 << 6); break;
    case B: MGPIOC_ODR &= ~((unsigned int)0x01 << 6); break;
    case W: MGPIOC_ODR &= ~((unsigned int)0x07 << 6); break;
    default: MGPIOC_ODR |= 0x07 << 6; break;
    }
}

void led_close_register(void) {
    MGPIOC_ODR |= 0x07 << 6;
}
