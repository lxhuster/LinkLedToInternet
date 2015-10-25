/**************************************************************************************
函数功能：USART1函数   发送  接收中断实现
**************************************************************************************/
#include<stm32f10x.h>
#include<misc.h>
#include<stm32f10x_usart.h>
#include<stdio.h>
/*******************************************************************************
函数名：fputc
输  入:
输  出:
功能说明：
重定义putc函数，这样可以使用printf函数从串口1打印输出
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
函数名：fputc   
输  入:    
输  出:    
功能说明：   
重定义getc函数，这样可以使用scanff函数从串口1输入数据*/
int fgetc(FILE *f)
{   
   /* 等待串口1输入数据 */  
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){}   
	return (int)USART_ReceiveData(USART1);	  
}
/***设置全局变量***/
unsigned char  test_value=0;
/***定串口发送标志***/
unsigned char  flag=0;
/***定USART1发送数组***/
unsigned char  u1test[50]="罗雄爱黄燕\r\n";
unsigned char  u2test[50]="huangyan ai luoxiong\n";

/*************************************************************************************
GPIO初始化函数
**************************************************************************************/
void GPIO_Configration()
{
   GPIO_InitTypeDef  GPIO_InitStruct;//定义GPIO结构体
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);//打开GPIOA的时钟
   GPIO_DeInit(GPIOA);//GPIOA的寄存器初始化
   GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9;//将USART1的TX设置为
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//频率设置到50MHz
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//管脚设置为复用推挽输出
   GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化

   GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10;//将USART1的TX设置为
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//频率设置为50MHz
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//管脚模式设置为浮空输入
   GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化


   GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;//将USART1的TX设置为
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//频率设置为50MHz
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//管脚模式设置为浮空输入
   GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化
}
/**********************************************************************************
中断设置初始化函数
***********************************************************************************/
void NVIC_Configration()
{
  NVIC_InitTypeDef   NVIC_InitStruct;//定义中断结构体
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//将优先级组别设置为0
  NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQChannel;//设置中断的通道为外部中断3
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;//抢先中断优先级设置为0
  NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;//子中断优先级设置为0
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//允许中断
  NVIC_Init(&NVIC_InitStruct);//中断的初始化
}
/*************************************************************************************
USART1初始化函数
**************************************************************************************/
void  USART_Configration()
{
   USART_InitTypeDef  USART_InitStruct;//定义串口结构体
   USART_DeInit(USART1);//UART1的寄存器初始化
   USART_InitStruct.USART_BaudRate=115200;//设置串口波特率为115200
   USART_InitStruct.USART_WordLength=USART_WordLength_8b;//设置一帧的数据位数
   USART_InitStruct.USART_StopBits=USART_StopBits_1;//设置停止位为1
   USART_InitStruct.USART_Parity=USART_Parity_No;//不进行奇偶校验
   USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//设置USART1的模式为全双工模式
   USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//没有硬件控制 
   USART_Init(USART1,&USART_InitStruct);//初始化

   //USART_ITConfig(USART1,USART_IT_TC,D);//允许相应的串口1的发送完成中断
   USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//允许相应的串口1的接收中断  
   USART_Cmd(USART1,ENABLE);//允许USART1开始工作	
}

/*************************************************************************************
总系统初始化函数
**************************************************************************************/
void sysinit()
{
    SystemInit ();
	GPIO_Configration();//GPIO初始化
	USART_Configration();//USART初始化
	NVIC_Configration();//中断初始化
}
/*************************************************************************************
主函数
**************************************************************************************/
int main()
{
   unsigned char  i;
   sysinit();//初始化
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
								while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//等待发送完成
								USART_ClearFlag(USART1,USART_FLAG_TC);//清除发送完中断标志
							  }
					     }break;
				 case(1):
						 {
						   	for(i=0;u2test[i]!='\0';i++)
							  {
							    USART_SendData(USART1,u2test[i]);
								while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//等待发送完成
								USART_ClearFlag(USART1,USART_FLAG_TC);//清除发送完中断标志
							  }
					     }break;
			   }
		   flag=0;//清除标志
		 }
	}  
}
