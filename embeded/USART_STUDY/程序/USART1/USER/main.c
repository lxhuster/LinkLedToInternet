/**************************************************************************************
�������ܣ�USART1����   ����  �����ж�ʵ��
**************************************************************************************/
#include<stm32f10x.h>
#include<misc.h>
#include<stm32f10x_usart.h>
#include<stdio.h>
/*******************************************************************************
��������fputc
��  ��:
��  ��:
����˵����
�ض���putc��������������ʹ��printf�����Ӵ���1��ӡ���
*/
int fputc(int ch, FILE *f)
{
	/* Place your implementation of fputc here */    
	/* e.g. write a character to the USART */ 
	USART_SendData(USART1, (uint8_t) ch);   
	/* Loop until the end of transmission */  
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}
	return ch;
}   

/*******************************************************************************
��������fputc   
��  ��:    
��  ��:    
����˵����   
�ض���getc��������������ʹ��scanff�����Ӵ���1��������*/
int fgetc(FILE *f)
{   
   /* �ȴ�����1�������� */  
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){}   
	return (int)USART_ReceiveData(USART1);	  
}
/***����ȫ�ֱ���***/
unsigned char  test_value=0;
/***�����ڷ��ͱ�־***/
unsigned char  flag=0;
/***��USART1��������***/
unsigned char  u1test[50]="���۰�����\r\n";
unsigned char  u2test[50]="huangyan ai luoxiong\n";

/*************************************************************************************
GPIO��ʼ������
**************************************************************************************/
void GPIO_Configration()
{
   GPIO_InitTypeDef  GPIO_InitStruct;//����GPIO�ṹ��
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);//��GPIOA��ʱ��
   GPIO_DeInit(GPIOA);//GPIOA�ļĴ�����ʼ��
   GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9;//��USART1��TX����Ϊ
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//Ƶ�����õ�50MHz
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//�ܽ�����Ϊ�����������
   GPIO_Init(GPIOA,&GPIO_InitStruct);//��ʼ��

   GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10;//��USART1��TX����Ϊ
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//Ƶ������Ϊ50MHz
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//�ܽ�ģʽ����Ϊ��������
   GPIO_Init(GPIOA,&GPIO_InitStruct);//��ʼ��


   GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;//��USART1��TX����Ϊ
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//Ƶ������Ϊ50MHz
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�ܽ�ģʽ����Ϊ��������
   GPIO_Init(GPIOA,&GPIO_InitStruct);//��ʼ��
}
/**********************************************************************************
�ж����ó�ʼ������
***********************************************************************************/
void NVIC_Configration()
{
  NVIC_InitTypeDef   NVIC_InitStruct;//�����жϽṹ��
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//�����ȼ��������Ϊ0
  NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQChannel;//�����жϵ�ͨ��Ϊ�ⲿ�ж�3
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;//�����ж����ȼ�����Ϊ0
  NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;//���ж����ȼ�����Ϊ0
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//�����ж�
  NVIC_Init(&NVIC_InitStruct);//�жϵĳ�ʼ��
}
/*************************************************************************************
USART1��ʼ������
**************************************************************************************/
void  USART_Configration()
{
   USART_InitTypeDef  USART_InitStruct;//���崮�ڽṹ��
   USART_DeInit(USART1);//UART1�ļĴ�����ʼ��
   USART_InitStruct.USART_BaudRate=115200;//���ô��ڲ�����Ϊ115200
   USART_InitStruct.USART_WordLength=USART_WordLength_8b;//����һ֡������λ��
   USART_InitStruct.USART_StopBits=USART_StopBits_1;//����ֹͣλΪ1
   USART_InitStruct.USART_Parity=USART_Parity_No;//��������żУ��
   USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//����USART1��ģʽΪȫ˫��ģʽ
   USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//û��Ӳ������ 
   USART_Init(USART1,&USART_InitStruct);//��ʼ��

   //USART_ITConfig(USART1,USART_IT_TC,D);//������Ӧ�Ĵ���1�ķ�������ж�
   USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//������Ӧ�Ĵ���1�Ľ����ж�  
   USART_Cmd(USART1,ENABLE);//����USART1��ʼ����	
}

/*************************************************************************************
��ϵͳ��ʼ������
**************************************************************************************/
void sysinit()
{
    SystemInit ();
	GPIO_Configration();//GPIO��ʼ��
	USART_Configration();//USART��ʼ��
	NVIC_Configration();//�жϳ�ʼ��
}
/*************************************************************************************
������
**************************************************************************************/
int main()
{
   unsigned char  i;
   sysinit();//��ʼ��
   while(1)
    {
		if(flag)
		  {
			 switch(test_value)
			  {
			     case(0):
						 {
						   	for(i=0;u1test[i]!='\0';i++)
							  {
							    USART_SendData(USART1,u1test[i]);
								while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//�ȴ��������
								USART_ClearFlag(USART1,USART_FLAG_TC);//����������жϱ�־
							  }
					     }break;
				 case(1):
						 {
						   	for(i=0;u2test[i]!='\0';i++)
							  {
							    USART_SendData(USART1,u2test[i]);
								while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//�ȴ��������
								USART_ClearFlag(USART1,USART_FLAG_TC);//����������жϱ�־
							  }
					     }break;
			   }
		   flag=0;//�����־
		 }
	}  
}
