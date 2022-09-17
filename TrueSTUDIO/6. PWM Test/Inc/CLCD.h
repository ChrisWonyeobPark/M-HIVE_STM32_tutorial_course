#ifndef _TEXTLCD_H
#define _TEXTLCD_H

#include "stm32f4xx_hal.h"

/*/////   PIN CONNECTION   /////*/
/*		CLCD_RS		PE0			*/
/*		CLCD_RW 	PE1			*/
/*		CLCD_EN 	PE2			*/
/*		CLCD_D4 	PE4			*/
/*		CLCD_D5 	PE5			*/
/*		CLCD_D6 	PE6			*/
/*		CLCD_D7 	PE7			*/
////////////////////////////////*/

#define GPIO_RS GPIOE
#define GPIO_RW GPIOE
#define GPIO_EN GPIOE
#define GPIO_D4	GPIOE
#define GPIO_D5	GPIOE
#define GPIO_D6	GPIOE
#define GPIO_D7	GPIOE

#define GPIO_PIN_RS	GPIO_PIN_0
#define GPIO_PIN_RW	GPIO_PIN_1
#define GPIO_PIN_EN	GPIO_PIN_2
#define GPIO_PIN_D4	GPIO_PIN_4
#define GPIO_PIN_D5	GPIO_PIN_5
#define GPIO_PIN_D6	GPIO_PIN_6
#define GPIO_PIN_D7	GPIO_PIN_7


void CLCD_GPIO_Init(void);
void CLCD_Write_Instruction(unsigned char b);
void CLCD_Write_Display(unsigned char b);
void CLCD_Gotoxy(unsigned char x, unsigned char y);
void CLCD_Puts(unsigned char x, unsigned char y, unsigned char *str);
void CLCD_Init(void);
void CLCD_Clear(void);
static void Delay(__IO uint32_t nCount);


#endif
