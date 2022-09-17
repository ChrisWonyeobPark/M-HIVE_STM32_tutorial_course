/*
 * This is a library for 16x2 character LCD.
 * This has been tested on M-HIVE STM32F4 EduBoard V1.2 (Evaluation board)
 * Buy on https://smartstore.naver.com/mhivestore
 *
 * Development environment specifics:
 * STM32F407VET6
 * Atollic TrueSTUDIO 9.0.1
 * CubeMX 4.26.0
 * STM32Cube FW_F4 V1.21.0
 * HAL Driver(RCC and GPIO)
 *
 * Written by ChrisP(Wonyeob Park) @ M-HIVE Embedded Academy, written when tigers used to smoke.
 * Rev. 1.0
 *
 * https://github.com/ChrisWonyeobPark/M-HIVE_STM32_tutorial_course
 * https://www.udemy.com/course/hal-cubemx-truestudio-stm32f4/?referralCode=E2BDCA5EFF512BF0E94E
 * https://www.inflearn.com/course/stm32f4
 */

#ifndef _CLCD_H
#define _CLCD_H

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


#endif
