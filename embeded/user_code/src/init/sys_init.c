/*
 *Abstract:Init the device of System
 *
 */
 
/* Includes */
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include <misc.h>

/* Declare all init func */
void Rcc_Config(void);
void Gpio_Config(void);
void Usart_Config(void);
void Nvic_Config(void);

/* Realization init interface func */
void Sys_Init(void)
{
  SystemInit();
	Rcc_Config();
	Gpio_Config();
	Usart_Config();
	Nvic_Config();
}
 
/*  Realization Init function */ 
void Rcc_Config(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
}

static void Gpio_ModeSet(GPIO_TypeDef* GPIOx, uint16_t Gpio_Pin, GPIOSpeed_TypeDef Gpio_Speed, GPIOMode_TypeDef Gpio_Mode)
{
    GPIO_InitTypeDef Gpio_InitStruct;
    Gpio_InitStruct.GPIO_Pin = Gpio_Pin;
    Gpio_InitStruct.GPIO_Speed = Gpio_Speed;
    Gpio_InitStruct.GPIO_Mode = Gpio_Mode;
    GPIO_Init(GPIOx,&Gpio_InitStruct);
}

void Gpio_Config(void)
{
/* Set Led Control I/O */	
	  GPIO_DeInit(GPIOB);
    Gpio_ModeSet(GPIOB, GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

/* Set Usart comunicate I/O */
	  GPIO_DeInit(GPIOA);
    Gpio_ModeSet(GPIOA, GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
    Gpio_ModeSet(GPIOA, GPIO_Pin_3, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);
}


void Nvic_Config(void)
{
  NVIC_InitTypeDef   NVIC_InitStruct;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQChannel;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
}


void  Usart_Config(void)
{
   USART_InitTypeDef  Usart_InitStruct;
   USART_DeInit(USART2);
   Usart_InitStruct.USART_BaudRate=115200;
   Usart_InitStruct.USART_WordLength=USART_WordLength_8b;
   Usart_InitStruct.USART_StopBits=USART_StopBits_1;
   Usart_InitStruct.USART_Parity=USART_Parity_No;
   Usart_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
   Usart_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
   USART_Init(USART2,&Usart_InitStruct);

   USART_ITConfig(USART2, USART_IT_RXNE,ENABLE); 
   USART_Cmd(USART2,ENABLE);	
}


 
