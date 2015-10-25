/*
 *Abstract:Application Func
 */
#include <stm32f10x.h>
#include <app.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>

/* Led Flag */
char ledFlag = 0;
char ledFlagChange = 0;

void abstract_ms_delay(u16 time)
{    
    u16 i=0;  
    while(time--)
    {
        i=12000;
        while(i--) ;    
    }
}

void Usart_Comunicate(char *msg)
{
	  if (msg == 0)
		{
        return;
		}
	  while(*msg != '\0')
		{
        USART_SendData(USART2, *msg);
			  msg++;
        while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);
		}
}

void led_app(void)
{
	  abstract_ms_delay(900);
	  if (ledFlagChange == 0)
		{
			return;
    }
		ledFlagChange = 0;
    if (ledFlag == LED_ON_FLAG)
		{
        LED_TURN_ON();
			  Usart_Comunicate("The Led is Turn On My Master");
			  return;
		}
    else if (ledFlag == LED_OFF_FLAG)
		{
        LED_TURN_OFF();
			  Usart_Comunicate("The Led DOwn My Master");
			  return;			
    }
		else
		{
        Usart_Comunicate("Wrong Cmd");			
    }
}
