/*
 *Abstract:Application Func
 */
#ifndef __APP_H
#define __APP_H

/* Defines */
#define LED_TURN_ON()   (GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET))
#define LED_TURN_OFF()  (GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_RESET))

#define LED_ON_FLAG ('O')
#define LED_OFF_FLAG ('N')

/* Decelare Led flag */
extern char ledFlag;
extern char ledFlagChange;

/* Decelare app funcs */
void led_app(void);
#endif

