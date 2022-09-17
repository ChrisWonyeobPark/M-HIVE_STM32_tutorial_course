#include "7seg.h"

void _7SEG_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIOA,D,E Periph clock enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	//Digit1
	GPIO_InitStruct.Pin = GPIO_PIN_DGT1_A;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIO_DGT1_A, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT1_B;
	HAL_GPIO_Init(GPIO_DGT1_B, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT1_C;
	HAL_GPIO_Init(GPIO_DGT1_C, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT1_D;
	HAL_GPIO_Init(GPIO_DGT1_D, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT1_E;
	HAL_GPIO_Init(GPIO_DGT1_E, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT1_F;
	HAL_GPIO_Init(GPIO_DGT1_F, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT1_G;
	HAL_GPIO_Init(GPIO_DGT1_G, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT1_DP;
	HAL_GPIO_Init(GPIO_DGT1_DP, &GPIO_InitStruct);

	//Digit2
	GPIO_InitStruct.Pin = GPIO_PIN_DGT2_A;
	HAL_GPIO_Init(GPIO_DGT2_A, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT2_B;
	HAL_GPIO_Init(GPIO_DGT2_B, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT2_C;
	HAL_GPIO_Init(GPIO_DGT2_C, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT2_D;
	HAL_GPIO_Init(GPIO_DGT2_D, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT2_E;
	HAL_GPIO_Init(GPIO_DGT2_E, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT2_F;
	HAL_GPIO_Init(GPIO_DGT2_F, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT2_G;
	HAL_GPIO_Init(GPIO_DGT2_G, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_DGT2_DP;
	HAL_GPIO_Init(GPIO_DGT2_DP, &GPIO_InitStruct);

	
	_7SEG_SetNumber(DGT1, 0, ON);
	_7SEG_SetNumber(DGT2, 0, ON);
}


void _7SEG_SetNumber(int dgt, int num, int dp)
{
	if(dgt == DGT1)
	{
		switch(num%10)
		{
			case 0: DGT1_A_ON; DGT1_B_ON; DGT1_C_ON; DGT1_D_ON; DGT1_E_ON; DGT1_F_ON;
					DGT1_G_OFF;
				break;
			case 1: DGT1_B_ON; DGT1_C_ON;
					DGT1_A_OFF; DGT1_D_OFF; DGT1_E_OFF; DGT1_F_OFF; DGT1_G_OFF;
				break;
			case 2: DGT1_A_ON; DGT1_B_ON; DGT1_G_ON; DGT1_E_ON; DGT1_D_ON;
					DGT1_C_OFF; DGT1_F_OFF;
				break;
			case 3: DGT1_A_ON; DGT1_B_ON; DGT1_C_ON; DGT1_D_ON; DGT1_G_ON;
					DGT1_E_OFF; DGT1_F_OFF;
				break;
			case 4: DGT1_F_ON; DGT1_G_ON; DGT1_B_ON; DGT1_C_ON;
					DGT1_A_OFF; DGT1_D_OFF; DGT1_E_OFF;
				break;
			case 5: DGT1_A_ON; DGT1_F_ON; DGT1_G_ON; DGT1_C_ON; DGT1_D_ON;
					DGT1_B_OFF; DGT1_E_OFF;
				break;
			case 6: DGT1_A_ON; DGT1_C_ON; DGT1_D_ON; DGT1_E_ON; DGT1_F_ON; DGT1_G_ON;
					DGT1_B_OFF;
				break;
			case 7: DGT1_F_ON; DGT1_A_ON; DGT1_B_ON; DGT1_C_ON;
					DGT1_D_OFF; DGT1_E_OFF; DGT1_G_OFF;
				break;
			case 8: DGT1_A_ON; DGT1_B_ON; DGT1_C_ON; DGT1_D_ON; DGT1_E_ON; DGT1_F_ON; DGT1_G_ON;
				break;
			case 9: DGT1_A_ON; DGT1_B_ON; DGT1_C_ON; DGT1_D_ON; DGT1_F_ON; DGT1_G_ON;
					DGT1_E_OFF;
				break;
		}

		if(dp == ON)
		{
			DGT1_DP_ON;
		}
		else if(dp == OFF)
		{
			DGT1_DP_OFF;
		}
	}
	else if(dgt == DGT2)
	{
		switch(num%10)
		{
			case 0: DGT2_A_ON; DGT2_B_ON; DGT2_C_ON; DGT2_D_ON; DGT2_E_ON; DGT2_F_ON;
					DGT2_G_OFF;
				break;
			case 1: DGT2_B_ON; DGT2_C_ON;
					DGT2_A_OFF; DGT2_D_OFF; DGT2_E_OFF; DGT2_F_OFF; DGT2_G_OFF;
				break;
			case 2: DGT2_A_ON; DGT2_B_ON; DGT2_G_ON; DGT2_E_ON; DGT2_D_ON;
					DGT2_C_OFF; DGT2_F_OFF;
				break;
			case 3: DGT2_A_ON; DGT2_B_ON; DGT2_C_ON; DGT2_D_ON; DGT2_G_ON;
					DGT2_E_OFF; DGT2_F_OFF;
				break;
			case 4: DGT2_F_ON; DGT2_G_ON; DGT2_B_ON; DGT2_C_ON;
					DGT2_A_OFF; DGT2_D_OFF; DGT2_E_OFF;
				break;
			case 5: DGT2_A_ON; DGT2_F_ON; DGT2_G_ON; DGT2_C_ON; DGT2_D_ON;
					DGT2_B_OFF; DGT2_E_OFF;
				break;
			case 6: DGT2_A_ON; DGT2_C_ON; DGT2_D_ON; DGT2_E_ON; DGT2_F_ON; DGT2_G_ON;
					DGT2_B_OFF;
				break;
			case 7: DGT2_F_ON; DGT2_A_ON; DGT2_B_ON; DGT2_C_ON;
					DGT2_D_OFF; DGT2_E_OFF; DGT2_G_OFF;
				break;
			case 8: DGT2_A_ON; DGT2_B_ON; DGT2_C_ON; DGT2_D_ON; DGT2_E_ON; DGT2_F_ON; DGT2_G_ON;
				break;
			case 9: DGT2_A_ON; DGT2_B_ON; DGT2_C_ON; DGT2_D_ON; DGT2_F_ON; DGT2_G_ON;
					DGT2_E_OFF;
				break;
		}

		if(dp == ON)
		{
			DGT2_DP_ON;
		}
		else if(dp == OFF)
		{
			DGT2_DP_OFF;
		}
	}
}
