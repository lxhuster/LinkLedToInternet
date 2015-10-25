/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.0.0
  * @date    04/06/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_usart.h"
extern __IO uint8_t TxCounter1;
extern __IO uint8_t TxCounter2;
extern __IO uint8_t RxCounter1; 
extern __IO uint8_t RxCounter2;
extern uint8_t NbrOfDataToTransfer1;
extern uint8_t NbrOfDataToTransfer2;
extern uint8_t NbrOfDataToRead1;
extern uint8_t NbrOfDataToRead2,rec_f;
/*******************************************************************************
定义SysTick寄存器地址
*******************************************************************************/
#define SYSTICK_CSR     (*((volatile unsigned long *) 0xE000E010))//定义SysTick控制寄存器
#define SYSTICK_RELOAD  (*((volatile unsigned long *) 0xE000E014))//定义SysTick重载值寄存器
#define SYSTICK_CURRENT (*((volatile unsigned long *) 0xE000E018))//定义SysTick当前值寄存器
#define SYSTICK_TENMS   (*((volatile unsigned long *) 0xE000E01C))//定义SysTick校准值寄存器
/** @addtogroup Template_Project
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
extern unsigned long TimingDelay;//定义延时的全局变量
extern unsigned char  test_value;
extern unsigned char  flag; 
/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
/*	SYSTICK_CURRENT=0;//将重载寄存器清0
	if(TimingDelay!=0)//如果TimingDelay不为0就将TimingDelay值减1
	 {
	   TimingDelay--;
	 }		*/
}
/***USART1的中断处理函数 ***/
void USART1_IRQHandler(void)
{
  if(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=RESET);//如果是发送完成中断就执行以下语句
   {
      if(USART_GetITStatus(USART1,USART_FLAG_TC)!=RESET)//如果发送中断挂起中断置位
	    {		   
		   USART_ClearITPendingBit(USART1,USART_FLAG_TC);//清除挂起的中断标志
		}
			  GPIO_WriteBit(GPIOA,GPIO_Pin_0|GPIO_Pin_1,Bit_SET);
   }
  if(USART_GetFlagStatus(USART1,USART_IT_RXNE)!=RESET);//如果是接收完成中断就执行以下语句
   {
      if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)//如果接收中断挂起中断置位
	    {		   
		   USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除挂起的中断标志
		}
	  test_value=(unsigned char )USART_ReceiveData(USART1);//将接收到得数据赋值给test_value
	  flag=1;//将标志置位

   }

   
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
