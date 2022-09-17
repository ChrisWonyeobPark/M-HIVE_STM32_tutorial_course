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

#include "CLCD.h"

void CLCD_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIOE Periph clock enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	/* Configure RS, RW, EN, D4, D5, D6, D7 in output pushpull mode */
	GPIO_InitStruct.Pin = GPIO_PIN_RS;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIO_RS, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_RW;
	HAL_GPIO_Init(GPIO_RW, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_EN;
	HAL_GPIO_Init(GPIO_EN, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_D4;
	HAL_GPIO_Init(GPIO_D4, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_D5;
	HAL_GPIO_Init(GPIO_D5, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_D6;
	HAL_GPIO_Init(GPIO_D6, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_D7;
	HAL_GPIO_Init(GPIO_D7, &GPIO_InitStruct);
}

void CLCD_Write_Instruction(unsigned char b)
{
	//상위 4비트
	GPIO_D7->ODR = (b & 0x80) ? GPIO_D7->ODR | GPIO_PIN_D7 : GPIO_D7->ODR & ~GPIO_PIN_D7; //D7
	GPIO_D6->ODR = (b & 0x40) ? GPIO_D6->ODR | GPIO_PIN_D6 : GPIO_D6->ODR & ~GPIO_PIN_D6; //D6
	GPIO_D5->ODR = (b & 0x20) ? GPIO_D5->ODR | GPIO_PIN_D5 : GPIO_D5->ODR & ~GPIO_PIN_D5; //D5
	GPIO_D4->ODR = (b & 0x10) ? GPIO_D4->ODR | GPIO_PIN_D4 : GPIO_D4->ODR & ~GPIO_PIN_D4; //D4
	
	GPIO_RS->ODR = GPIO_RS->ODR & ~GPIO_PIN_RS; //RS를 Low
	GPIO_RW->ODR = GPIO_RW->ODR & ~GPIO_PIN_RW; //RW를 Low
	GPIO_EN->ODR = GPIO_EN->ODR & ~GPIO_PIN_EN; //EN를 Low
	
	GPIO_EN->ODR = GPIO_EN->ODR | GPIO_PIN_EN; //EN를 High
	GPIO_EN->ODR = GPIO_EN->ODR & ~GPIO_PIN_EN; //EN를 Low
	
	//하위 4비트
	GPIO_D7->ODR = (b & 0x08) ? GPIO_D7->ODR | GPIO_PIN_D7 : GPIO_D7->ODR & ~GPIO_PIN_D7; //D7
	GPIO_D6->ODR = (b & 0x04) ? GPIO_D6->ODR | GPIO_PIN_D6 : GPIO_D6->ODR & ~GPIO_PIN_D6; //D6
	GPIO_D5->ODR = (b & 0x02) ? GPIO_D5->ODR | GPIO_PIN_D5 : GPIO_D5->ODR & ~GPIO_PIN_D5; //D5
	GPIO_D4->ODR = (b & 0x01) ? GPIO_D4->ODR | GPIO_PIN_D4 : GPIO_D4->ODR & ~GPIO_PIN_D4; //D4

	GPIO_RS->ODR = GPIO_RS->ODR & ~GPIO_PIN_RS; //RS를 Low
	GPIO_RW->ODR = GPIO_RW->ODR & ~GPIO_PIN_RW; //RW를 Low
	GPIO_EN->ODR = GPIO_EN->ODR & ~GPIO_PIN_EN; //EN를 Low

	GPIO_EN->ODR = GPIO_EN->ODR | GPIO_PIN_EN; //EN를 High
	GPIO_EN->ODR = GPIO_EN->ODR & ~GPIO_PIN_EN; //EN를 Low

	HAL_Delay(1);
}

void CLCD_Write_Display(unsigned char b)
{
	//상위 4비트
	GPIO_D7->ODR = (b & 0x80) ? GPIO_D7->ODR | GPIO_PIN_D7 : GPIO_D7->ODR & ~GPIO_PIN_D7; //D7
	GPIO_D6->ODR = (b & 0x40) ? GPIO_D6->ODR | GPIO_PIN_D6 : GPIO_D6->ODR & ~GPIO_PIN_D6; //D6
	GPIO_D5->ODR = (b & 0x20) ? GPIO_D5->ODR | GPIO_PIN_D5 : GPIO_D5->ODR & ~GPIO_PIN_D5; //D5
	GPIO_D4->ODR = (b & 0x10) ? GPIO_D4->ODR | GPIO_PIN_D4 : GPIO_D4->ODR & ~GPIO_PIN_D4; //D4
	
	GPIO_RS->ODR = GPIO_RS->ODR | GPIO_PIN_RS; //RS를 High
	GPIO_RW->ODR = GPIO_RW->ODR & ~GPIO_PIN_RW; //RW를 Low
	GPIO_EN->ODR = GPIO_EN->ODR & ~GPIO_PIN_EN; //EN를 Low
	
	GPIO_EN->ODR = GPIO_EN->ODR | GPIO_PIN_EN; //EN를 High
	GPIO_EN->ODR = GPIO_EN->ODR & ~GPIO_PIN_EN; //EN를 Low
	
	//하위 4비트
	GPIO_D7->ODR = (b & 0x08) ? GPIO_D7->ODR | GPIO_PIN_D7 : GPIO_D7->ODR & ~GPIO_PIN_D7; //D7
	GPIO_D6->ODR = (b & 0x04) ? GPIO_D6->ODR | GPIO_PIN_D6 : GPIO_D6->ODR & ~GPIO_PIN_D6; //D6
	GPIO_D5->ODR = (b & 0x02) ? GPIO_D5->ODR | GPIO_PIN_D5 : GPIO_D5->ODR & ~GPIO_PIN_D5; //D5
	GPIO_D4->ODR = (b & 0x01) ? GPIO_D4->ODR | GPIO_PIN_D4 : GPIO_D4->ODR & ~GPIO_PIN_D4; //D4
	
	GPIO_RS->ODR = GPIO_RS->ODR | GPIO_PIN_RS; //RS를 High
	GPIO_RW->ODR = GPIO_RW->ODR & ~GPIO_PIN_RW; //RW를 Low
	GPIO_EN->ODR = GPIO_EN->ODR & ~GPIO_PIN_EN; //EN를 Low
	
	GPIO_EN->ODR = GPIO_EN->ODR | GPIO_PIN_EN; //EN를 High
	GPIO_EN->ODR = GPIO_EN->ODR & ~GPIO_PIN_EN; //EN를 Low
	
	HAL_Delay(1);
}


void CLCD_Gotoxy(unsigned char x, unsigned char y)
{
	// 16 * 2 character LCD
	switch(y)
	{
		case 0 : CLCD_Write_Instruction(0x80 + x); break;
		case 1 : CLCD_Write_Instruction(0xC0 + x); break;
		//case 2 : CLCD_Write_Instruction(0x90+x); break; //Uncomment for 16 * 4 character LCD
		//case 3 : CLCD_Write_Instruction(0xd0+x); break; //Uncomment for 16 * 4 character LCD
	}
}

void CLCD_Puts(unsigned char x, unsigned char y, unsigned char *str)
{
	unsigned int i=0;

	CLCD_Gotoxy(x,y);
	do
	{
		CLCD_Write_Display(str[i]);
	}
	while(str[++i]!='\0');
}

void CLCD_Init(void)
{
	HAL_Delay(100);
	CLCD_Write_Instruction(0x28);
	HAL_Delay(10);
	CLCD_Write_Instruction(0x28);
	HAL_Delay(10);
	CLCD_Write_Instruction(0x0C);
	CLCD_Write_Instruction(0x06);
	CLCD_Write_Instruction(0x02);
	CLCD_Write_Instruction(0x01);
	CLCD_Write_Instruction(0x01);
}

void CLCD_Clear(void)
{
	CLCD_Write_Instruction(0x01);
	HAL_Delay(10);
}
