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
����SysTick�Ĵ�����ַ
*******************************************************************************/
#define SYSTICK_CSR     (*((volatile unsigned long *) 0xE000E010))//����SysTick���ƼĴ���
#define SYSTICK_RELOAD  (*((volatile unsigned long *) 0xE000E014))//����SysTick����ֵ�Ĵ���
#define SYSTICK_CURRENT (*((volatile unsigned long *) 0xE000E018))//����SysTick��ǰֵ�Ĵ���
#define SYSTICK_TENMS   (*((volatile unsigned long *) 0xE000E01C))//����SysTickУ׼ֵ�Ĵ���
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
extern unsigned long TimingDelay;//������ʱ��ȫ�ֱ���
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
/*	SYSTICK_CURRENT=0;//�����ؼĴ�����0
	if(TimingDelay!=0)//���TimingDelay��Ϊ0�ͽ�TimingDelayֵ��1
	 {
	   TimingDelay--;
	 }		*/
}
/***USART1���жϴ����� ***/
void USART1_IRQHandler(void)
{
  if(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=RESET);//����Ƿ�������жϾ�ִ���������
   {
      if(USART_GetITStatus(USART1,USART_FLAG_TC)!=RESET)//��������жϹ����ж���λ
	    {		   
		   USART_ClearITPendingBit(USART1,USART_FLAG_TC);//���������жϱ�־
		}
			  GPIO_WriteBit(GPIOA,GPIO_Pin_0|GPIO_Pin_1,Bit_SET);
   }
  if(USART_GetFlagStatus(USART1,USART_IT_RXNE)!=RESET);//����ǽ�������жϾ�ִ���������
   {
      if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)//��������жϹ����ж���λ
	    {		   
		   USART_ClearITPendingBit(USART1,USART_IT_RXNE);//���������жϱ�־
		}
	  test_value=(unsigned char )USART_ReceiveData(USART1);//�����յ������ݸ�ֵ��test_value
	  flag=1;//����־��λ

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
