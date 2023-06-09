#include "drv_usart1_it.h"

void usart1_it_config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    // 发送端gpio
    GPIO_InitTypeDef gpioa_Init_struct;
    gpioa_Init_struct.GPIO_Pin = GPIO_Pin_9;
    gpioa_Init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioa_Init_struct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &gpioa_Init_struct);

    // 接收端gpio
    gpioa_Init_struct.GPIO_Pin = GPIO_Pin_10;
    gpioa_Init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpioa_Init_struct);

    // usart 配置
    USART_InitTypeDef usart_init_struct;
    usart_init_struct.USART_BaudRate = 115200;
    usart_init_struct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    usart_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_init_struct.USART_Parity = USART_Parity_No;
    usart_init_struct.USART_StopBits = USART_StopBits_1;
    usart_init_struct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &usart_init_struct);

    NVIC_InitTypeDef NVIC_InitStruct;
    // 配置串口中断源-----接收寄存器非空
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    // 给中断源配置具体的中断优先级
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;         // 查询stm32f10x.h文件的typedef enum IRQn
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;           // 使能中断通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; // 主优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;        // 子优先级
    NVIC_Init(&NVIC_InitStruct);

    USART_ClearFlag(USART1, USART_FLAG_TXE | USART_FLAG_TC);
    USART_Cmd(USART1, ENABLE);
}

int fputc(int ch, FILE *f) {
    USART_SendData(USART1, ch);
    while (SET != USART_GetFlagStatus(USART1, USART_FLAG_TXE)) {}
    USART_ClearFlag(USART1, USART_FLAG_TXE);
    return ch;
}
