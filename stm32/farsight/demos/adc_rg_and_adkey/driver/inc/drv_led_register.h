#ifndef __DRV_LED_REGISTER_H__
#define __DRV_LED_REGISTER_H__

typedef enum e_LedColorRigister {
    R = 0,
    G,
    B,
    W
} LedColorRigister;

#define MGPIOC_ADDR 0x40011000

#define MGPIOC_CRL (*(volatile unsigned int *)(MGPIOC_ADDR + 0x00))
#define MGPIOC_CRH (*(volatile unsigned int *)(MGPIOC_ADDR + 0x04))

#define MGPIOC_ODR (*(volatile unsigned int *)(MGPIOC_ADDR + 0x0c))

#define RCC_MGPIOC_ADDR (0x40021000)
#define RCC_MGPIOC (*(volatile unsigned int *)(RCC_MGPIOC_ADDR + 0x18))

extern void led_config_register(void);
extern void led_open_register(LedColorRigister color);
extern void led_close_register(void);

#endif
