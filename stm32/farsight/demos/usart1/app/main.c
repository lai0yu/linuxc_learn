#include "stdint.h"
uint8_t is_led_on = 0xff;

#define OPEN_DEMO_13

/*********************************Demo1***************************************/
#ifdef OPEN_DEMO_1
#include "drv_led.h"
int main(void) {
    led_config();
    while (1) {
        led_open();
    }
}
/*********************************EndDemo1*************************************/

/*********************************Demo2****************************************/
#elif defined OPEN_DEMO_2
#include "drv_led_register.h"
void delay(void) {
    int i = 0;
    for (i = 0; i < 3000000; i++) {
        ;
    }
}
int main(void) {
    led_config_register();
    while (1) {
        led_open_register(W);
        delay();
        led_open_register(R);
        delay();
        led_open_register(G);
        delay();
        led_open_register(B);
        delay();
    }
}
/*********************************EndDemo2*************************************/

/*********************************Demo3****************************************/
#elif defined OPEN_DEMO_3
#include "drv_led_register.h"
#include "drv_sysclk.h"
void delay(void) {
    int i = 0;
    for (i = 0; i < 3000000; i++) {
        ;
    }
}
int main(void) {
    RCC_DeInit();
    rcc_init_72m();
    led_config_register();
    while (1) {
        led_open_register(W);
        delay();
        led_open_register(R);
        delay();
        led_open_register(G);
        delay();
        led_open_register(B);
        delay();
    }
}
/*********************************EndDemo3*************************************/

/*********************************Demo4****************************************/
#elif defined OPEN_DEMO_4
#include "drv_led_register.h"
#include "drv_sysclk.h"
#include "drv_systick.h"
int main(void) {
    RCC_DeInit();
    rcc_init_72m();
    systick_config(72);
    led_config_register();
    while (1) {
        led_open_register(W);
        systick_delay_ms(2500);
        led_open_register(R);
        systick_delay_ms(2500);
        led_open_register(G);
        systick_delay_ms(2500);
        led_open_register(B);
        systick_delay_ms(2500);
    }
}
/*********************************EndDemo4*************************************/

/*********************************Demo5****************************************/
#elif defined OPEN_DEMO_5
#include "drv_led_register.h"
#include "drv_sysclk.h"
#include "drv_keypress.h"
int main(void) {
    RCC_DeInit();
    rcc_init_72m();
    led_config_register();
    key_config();
    while (1) {
        if (is_key_press()) {
            is_led_on = ~is_led_on;
        }
        if (is_led_on) {
            led_close_register();
        } else {
            led_open_register(W);
        }
    }
}
/*********************************EndDemo5*************************************/

/*********************************Demo6****************************************/
#elif defined OPEN_DEMO_6
#include "drv_sysclk.h"
#include "drv_usart1.h"
int main(void) {
    RCC_DeInit();
    rcc_init_72m();
    usart1_config();
    printf("hello world!\n");
    while (1) {
        USART_SendData(USART1, 0x77);
        if (SET == USART_GetFlagStatus(USART1, USART_FLAG_RXNE)) {
            USART_ClearFlag(USART1, USART_FLAG_RXNE);
            USART_SendData(USART1, USART_ReceiveData(USART1));
        }
    }
}
/*********************************EndDemo6*************************************/

/*********************************Demo7****************************************/
#elif defined OPEN_DEMO_7
#include "drv_led_register.h"
#include "drv_sysclk.h"
#include "drv_usart1_it.h"
int main(void) {
    RCC_DeInit();
    rcc_init_72m();
    led_config_register();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    usart1_it_config();
    while (1) {
        if (is_led_on) {
            led_open_register(R);
        } else {
            led_close_register();
        }
    }
}
/*********************************EndDemo7*************************************/

/*********************************Demo8****************************************/
#elif defined OPEN_DEMO_8
#include "drv_led_register.h"
#include "drv_sysclk.h"
#include "drv_keypress_exti.h"

int main(void) {
    RCC_DeInit();
    rcc_init_72m();
    led_config_register();
    drv_keypress_it_config();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    while (1) {
        if (is_led_on) {
            led_open_register(R);
        } else {
            led_close_register();
        }
    }
}
/*********************************EndDemo8*************************************/

/*********************************Demo9****************************************/
#elif defined OPEN_DEMO_9
#include "drv_led_register.h"
#include "drv_sysclk.h"
#include "drv_tim6_it.h"
int main(void) {
    RCC_DeInit();
    rcc_init_72m();
    led_config_register();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    tim6_it_config();
    while (1) {
        if (is_led_on) {
            led_open_register(R);
        } else {
            led_close_register();
        }
    }
}
/*********************************EndDemo9*************************************/

/*********************************Demo10***************************************/
#elif defined OPEN_DEMO_10
#include "drv_sysclk.h"
#include "drv_common_tim3.h"
int main(void) {
    RCC_DeInit();
    rcc_init_72m();
    common_tim3_config();
    while (1) {
        set_tim3_compare_value(251, 19, 223);
    }
}
/*********************************EndDemo10************************************/

/*********************************Demo11***************************************/
#elif defined OPEN_DEMO_11
#include "drv_sysclk.h"
#include "drv_tim3_it_breath.h"
int main(void) {
    RCC_DeInit();
    rcc_init_72m();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    tim3_it_breath_config();
    while (1) {}
}
/*********************************EndDemo11************************************/

/*********************************Demo12***************************************/
#elif defined OPEN_DEMO_12
#include "drv_sysclk.h"
#include "drv_led_register.h"
#include "drv_dma.h"
uint32_t src[1000] = {0};
uint32_t dst[1000] = {0};
int main(void) {
    int i;
    for (i = 0; i < 1000; i++) {
        src[i] = i + 1;
    }
    RCC_DeInit();
    rcc_init_72m();
    led_config_register();
    dma_config(src, dst, 1000);
    led_open_register(R);
    while (SET != DMA_GetFlagStatus(DMA1_FLAG_TC2)) {}
    DMA_ClearFlag(DMA1_FLAG_TC2);
    if (is_dma_finish(src, dst, 1000)) {
        led_open_register(G);
    }
    while (1) {}
}
/*********************************EndDemo12************************************/
/*********************************Demo13***************************************/
#elif defined OPEN_DEMO_13
#include "drv_sysclk.h"
#include "drv_led_register.h"
#include "drv_dma.h"
uint32_t src[1000] = {0};
uint32_t dst[1000] = {0};
int main(void) {
    int i;
    for (i = 0; i < 1000; i++) {
        src[i] = i + 1;
    }
    RCC_DeInit();
    rcc_init_72m();
    led_config_register();
    dma_config(src, dst, 1000);
    led_open_register(R);
    while (SET != DMA_GetFlagStatus(DMA1_FLAG_TC2)) {}
    DMA_ClearFlag(DMA1_FLAG_TC2);
    if (is_dma_finish(src, dst, 1000)) {
        led_open_register(G);
    }
    while (1) {}
}
/*********************************EndDemo13************************************/
#else
int main(void) {
    while (1) {}
}
#endif
