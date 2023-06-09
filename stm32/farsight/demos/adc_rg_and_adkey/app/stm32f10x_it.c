/**
 ******************************************************************************
 * @file    GPIO/IOToggle/stm32f10x_it.c
 * @author  MCD Application Team
 * @version V3.5.0
 * @date    08-April-2011
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and peripherals
 *          interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
 * @{
 */

/** @addtogroup GPIO_IOToggle
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void) {
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void) {
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void) {
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void) {
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void) {
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void) {
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void) {
}

/**
 * @brief  This function handles PendSV_Handler exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void) {
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void) {
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
uint8_t char_count = 0;
char usart1_recv_buf[10] = {0};
void USART1_IRQHandler(void) {
    if (SET == USART_GetITStatus(USART1, USART_IT_RXNE)) {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        USART_SendData(USART1, USART_ReceiveData(USART1));
        usart1_recv_buf[char_count] = USART_ReceiveData(USART1);
        char_count++;
        usart1_recv_buf[char_count] = '\0';
    }

    if (SET == USART_GetITStatus(USART1, USART_IT_IDLE)) {
        USART_ReceiveData(USART1);
        if (0 == strcmp(usart1_recv_buf, "open")) {
            is_led_on = 0xff;
        } else if (0 == strcmp(usart1_recv_buf, "close")) {
            is_led_on = 0x00;
        }
        char_count = 0;
        memset(usart1_recv_buf, 0, sizeof(usart1_recv_buf));
    }
}

void EXTI0_IRQHandler(void) {
    if (SET == EXTI_GetITStatus(EXTI_Line0)) {
        EXTI_ClearITPendingBit(EXTI_Line0);
        is_led_on = ~is_led_on;
    }
}

void TIM6_IRQHandler(void) {
    if (SET == TIM_GetFlagStatus(TIM6, TIM_IT_Update)) {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
        is_led_on = ~is_led_on;
    }
}

uint32_t angle = 0;
double sin_ret;
double radius;
int light;
void TIM3_IRQHandler(void) {
    if (SET == TIM_GetITStatus(TIM3, TIM_IT_Update)) {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        angle++;
        radius = DEG_TO_RAD(angle / 100);
        sin_ret = sin(radius) / 2 + 0.5;
        light = (int)(sin_ret * 255);
        set_tim3_compare_breath_value(light, 0, 0);
    }
}
/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
{
}*/

/**
 * @}
 */

/**
 * @}
 */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
