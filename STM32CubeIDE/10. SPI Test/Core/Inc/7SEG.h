/*
 * This is a library for SR-2056A 7-segment numeric display.
 * This has been tested on M-HIVE STM32F4 EduBoard V1.2 (Evaluation board)
 * Buy on https://smartstore.naver.com/mhivestore/products/4953744659
 *
 * Development environment specifics:
 * STM32F407VET6
 * Atollic TrueSTUDIO 9.0.1 with CubeMX 4.26.0
 * STM32CubeIDE 1.10.0
 * STM32Cube FW_F4 V1.21.0
 * STM32Cube FW_F4 V1.27.1
 * HAL Driver(RCC and GPIO)
 *
 * Written by ChrisP(Wonyeob Park) @ M-HIVE Embedded Academy, 2017.
 * Rev. 1.0
 *
 * https://github.com/ChrisWonyeobPark/M-HIVE_STM32_tutorial_course
 * https://www.youtube.com/playlist?list=PLUaCOzp6U-RqMo-QEJQOkVOl1Us8BNgXk
 * https://www.udemy.com/course/hal-cubemx-truestudio-stm32f4/?referralCode=E2BDCA5EFF512BF0E94E
 * https://www.inflearn.com/course/stm32f4
 */

#ifndef _7SEG_H
#define _7SEG_H

#include "stm32f4xx_hal.h"

/*********************************************************

	SR-2056A (Common Anode 2digits 7segment. 18pin)

			A(PD11)                        A(PE9)
		    _________                     _________
		   |         |                   |         |
   (PC13)F |         | B(PA8)     (PE8)F |         | B(PE10)
		   |         |                   |         |
		    _________                     _________
		   | G(PD15) |                   | G(PE13) |
   (PC14)E |         | C(PD6)    (PE15)E |         | C(PE12)
		   |         |                   |         |
		    _________  @ DP(PD7)          _________  @ DP(PE11)
			D(PD5)                        D(PE14)
			
			DIGIT_1ST					DIGIT_2ND

Set: turn off
Reset: turn on
*********************************************************/

#define ON 1
#define OFF 0
#define DGT1 0
#define DGT2 1

#define GPIO_PIN_DGT1_A		GPIO_PIN_11
#define GPIO_DGT1_A			GPIOD
#define GPIO_PIN_DGT1_B		GPIO_PIN_8
#define GPIO_DGT1_B			GPIOA
#define GPIO_PIN_DGT1_C		GPIO_PIN_6
#define GPIO_DGT1_C			GPIOD
#define GPIO_PIN_DGT1_D		GPIO_PIN_5
#define GPIO_DGT1_D			GPIOD
#define GPIO_PIN_DGT1_E		GPIO_PIN_14
#define GPIO_DGT1_E			GPIOC
#define GPIO_PIN_DGT1_F		GPIO_PIN_13
#define GPIO_DGT1_F			GPIOC
#define GPIO_PIN_DGT1_G		GPIO_PIN_15
#define GPIO_DGT1_G			GPIOD
#define GPIO_PIN_DGT1_DP	GPIO_PIN_7
#define GPIO_DGT1_DP		GPIOD

#define GPIO_PIN_DGT2_A		GPIO_PIN_9
#define GPIO_DGT2_A			GPIOE
#define GPIO_PIN_DGT2_B		GPIO_PIN_10
#define GPIO_DGT2_B			GPIOE
#define GPIO_PIN_DGT2_C		GPIO_PIN_12
#define GPIO_DGT2_C			GPIOE
#define GPIO_PIN_DGT2_D		GPIO_PIN_14
#define GPIO_DGT2_D			GPIOE
#define GPIO_PIN_DGT2_E		GPIO_PIN_15
#define GPIO_DGT2_E			GPIOE
#define GPIO_PIN_DGT2_F		GPIO_PIN_8
#define GPIO_DGT2_F			GPIOE
#define GPIO_PIN_DGT2_G		GPIO_PIN_13
#define GPIO_DGT2_G			GPIOE
#define GPIO_PIN_DGT2_DP	GPIO_PIN_11
#define GPIO_DGT2_DP		GPIOE

#define DGT1_A_ON	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET)
#define DGT1_A_OFF	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET)
#define DGT1_B_ON	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET)
#define DGT1_B_OFF	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET)
#define DGT1_C_ON	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET)
#define DGT1_C_OFF	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET)
#define DGT1_D_ON	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET)
#define DGT1_D_OFF	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET)
#define DGT1_E_ON	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET)
#define DGT1_E_OFF	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET)
#define DGT1_F_ON	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)
#define DGT1_F_OFF	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)
#define DGT1_G_ON	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET)
#define DGT1_G_OFF	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET)
#define DGT1_DP_ON	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET)
#define DGT1_DP_OFF	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET)

#define DGT2_A_ON	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET)
#define DGT2_A_OFF	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET)
#define DGT2_B_ON	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET)
#define DGT2_B_OFF	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET)
#define DGT2_C_ON	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET)
#define DGT2_C_OFF	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET)
#define DGT2_D_ON	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET)
#define DGT2_D_OFF	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET)
#define DGT2_E_ON	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET)
#define DGT2_E_OFF	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET)
#define DGT2_F_ON	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET)
#define DGT2_F_OFF	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET)
#define DGT2_G_ON	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET)
#define DGT2_G_OFF	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET)
#define DGT2_DP_ON	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET)
#define DGT2_DP_OFF	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET)



void _7SEG_GPIO_Init();
void _7SEG_SetNumber(int digit, int num, int dp);

#endif
