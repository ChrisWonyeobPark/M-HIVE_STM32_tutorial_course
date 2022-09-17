
/* Includes ------------------------------------------------------------------*/
#include "VS1003.h"

uint8_t vs1003ram[5] = { 0 , 0 , 0 , 0 , 250 };

SPI_HandleTypeDef hspi2;

/* SPI2 init function */
void VS1003_SPI_Init(void)
{
	/* SPI2 clock enable */
	__HAL_RCC_SPI2_CLK_ENABLE();

	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 0;
	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		Error_Handler();
	}
}

/*******************************************************************************
* Function Name  : VS1003_Init
* Description    : VS1003 SPI and GPIO Initialization
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO clock enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/* /CS */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;//GPIO_PULLUP //GPIO_NOPULL
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* XDCS */
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* XRESET */
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* DREQ */
	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/**SPI2 GPIO Configuration
	PB10     ------> SPI2_SCK
	PB14     ------> SPI2_MISO
	PB15     ------> SPI2_MOSI
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	MP3_RESET(0);
	HAL_Delay(1);
	MP3_RESET(1);

	MP3_DCS(1);
	MP3_CCS(1);

	VS1003_SPI_Init();
}

/*******************************************************************************
* Function Name  : VS1003_SPI_SetSpeed
* Description    : None
* Input          : - SpeedSet: SPI_SPEED_HIGH 1  SPI_SPEED_LOW 0
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void VS1003_SPI_SetSpeed(uint8_t SpeedSet)
{
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 0;

	if(SpeedSet == SPI_SPEED_LOW)
	{
		hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	}
	else
	{
		hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	}

	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		Error_Handler();
	}
}


/*******************************************************************************
* Function Name  : VS1003_SPI_ReadWriteByte
* Description    : None
* Input          : - TxData: Write Byte
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static uint16_t VS1003_SPI_ReadWriteByte(uint16_t TxData)
{
	uint8_t RxData;
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)&TxData, &RxData, 1, 10);
	return RxData;
}


/*******************************************************************************
* Function Name  : VS1003_WriteReg
* Description    : VS1003 ∑π¡ˆΩ∫≈Õ º≥¡§
* Input          : - reg: ∑π¡ˆΩ∫≈Õ ¡÷º“?
*			    - value: æµ µ•¿Ã≈Õ
* Output         : None
* Return         : None
* Attention	  : None
*******************************************************************************/
void VS1003_WriteReg(uint8_t reg, uint16_t value)
{
	while(MP3_DREQ == 0);

	VS1003_SPI_SetSpeed(SPI_SPEED_LOW);
	MP3_DCS(1);
	MP3_CCS(0);
	VS1003_SPI_ReadWriteByte(VS1003_WRITE_COMMAND);
	VS1003_SPI_ReadWriteByte(reg);
	VS1003_SPI_ReadWriteByte(value >> 8);
	VS1003_SPI_ReadWriteByte(value);
	MP3_CCS(1);
	VS1003_SPI_SetSpeed(SPI_SPEED_HIGH);
}

/*******************************************************************************
* Function Name  : VS1003_ReadReg
* Description    : VS1003 ∑π¡ˆΩ∫≈Õ ¿–±‚
* Input          : - reg: ∑π¡ˆΩ∫≈Õ ¡÷º“?
* Output         : None
* Return         : - value: ¿–æÓø¬ µ•¿Ã≈Õ
* Attention	  : None
*******************************************************************************/
uint16_t VS1003_ReadReg(uint8_t reg)
{
	uint16_t value;

	while(MP3_DREQ == 0);
	VS1003_SPI_SetSpeed(SPI_SPEED_LOW );
	MP3_DCS(1);
	MP3_CCS(0);
	VS1003_SPI_ReadWriteByte(VS1003_READ_COMMAND);
	VS1003_SPI_ReadWriteByte(reg);
	value = VS1003_SPI_ReadWriteByte(0xff);
	value = value << 8;
	value |= VS1003_SPI_ReadWriteByte(0xff);
	MP3_CCS(1);
	VS1003_SPI_SetSpeed(SPI_SPEED_HIGH);
	return value;
}

/*******************************************************************************
* Function Name  : VS1003_ResetDecodeTime
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention	  : None
*******************************************************************************/
void VS1003_ResetDecodeTime(void)
{
	VS1003_WriteReg(SPI_DECODE_TIME, 0x0000);
	VS1003_WriteReg(SPI_DECODE_TIME, 0x0000);
}

/*******************************************************************************
* Function Name  : VS1003_GetDecodeTime
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention	  : None
*******************************************************************************/
uint16_t VS1003_GetDecodeTime(void)
{
	return VS1003_ReadReg(SPI_DECODE_TIME);
}

/*******************************************************************************
* Function Name  : VS1003_SoftReset
* Description    : VS1003 Soft Reset
* Input          : None
* Output         : None
* Return         : None
* Attention	  : None
*******************************************************************************/
void VS1003_SoftReset(void)
{
	uint8_t retry;

	while(MP3_DREQ == 0);
	VS1003_SPI_ReadWriteByte(0xff);
	retry = 0;
	while(VS1003_ReadReg(SPI_MODE) != 0x0804)
	{
		VS1003_WriteReg(SPI_MODE, 0x0804);
		HAL_Delay(2);
		if(retry++ > 100)
		{
			break;
		}
	}

	while(MP3_DREQ == 0);
	retry = 0;
	while( VS1003_ReadReg(SPI_CLOCKF) != 0x9800)
	{
		VS1003_WriteReg(SPI_CLOCKF, 0x9800);
		if(retry++ > 100)
		{
			break;
		}
	}

	retry = 0;
	while( VS1003_ReadReg(SPI_AUDATA) != 0xBB81)
	{
		VS1003_WriteReg(SPI_AUDATA, 0xBB81);
		if(retry++ > 100)
		{
			break;
		}
	}

	VS1003_WriteReg(SPI_VOL, 0x0000);
	VS1003_ResetDecodeTime();

	MP3_DCS(0);
	VS1003_SPI_ReadWriteByte(0xFF);
	VS1003_SPI_ReadWriteByte(0xFF);
	VS1003_SPI_ReadWriteByte(0xFF);
	VS1003_SPI_ReadWriteByte(0xFF);
	MP3_DCS(1);
	HAL_Delay(20);
}

/*******************************************************************************
* Function Name  : VS1003_Reset
* Description    : VS1003∏¥Œª
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003_Reset(void)
{
	MP3_RESET(0);
	HAL_Delay(20);
	MP3_RESET(1);
	HAL_Delay(20);
	VS1003_SPI_ReadWriteByte(0xFF);
	MP3_DCS(1);
	MP3_CCS(1);
	while(MP3_DREQ == 0);
	HAL_Delay(20);
}

/*******************************************************************************
* Function Name  : VS1003_SineTest
* Description    : VS1003’˝œ“≤‚ ‘
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003_SineTest(void)
{
	VS1003_WriteReg(SPI_VOL, 0x2020);
	VS1003_WriteReg(SPI_MODE, 0x0820);
	while(MP3_DREQ == 0);

	MP3_DCS(0);
	VS1003_SPI_ReadWriteByte(0x53);
	VS1003_SPI_ReadWriteByte(0xef);
	VS1003_SPI_ReadWriteByte(0x6e);
	VS1003_SPI_ReadWriteByte(0x24);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	HAL_Delay(100);
	MP3_DCS(1);

	MP3_DCS(0);
	VS1003_SPI_ReadWriteByte(0x45);
	VS1003_SPI_ReadWriteByte(0x78);
	VS1003_SPI_ReadWriteByte(0x69);
	VS1003_SPI_ReadWriteByte(0x74);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	HAL_Delay(100);
	MP3_DCS(1);

	MP3_DCS(0);
	VS1003_SPI_ReadWriteByte(0x53);
	VS1003_SPI_ReadWriteByte(0xef);
	VS1003_SPI_ReadWriteByte(0x6e);
	VS1003_SPI_ReadWriteByte(0x44);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	HAL_Delay(100);
	MP3_DCS(1);

	MP3_DCS(0);
	VS1003_SPI_ReadWriteByte(0x45);
	VS1003_SPI_ReadWriteByte(0x78);
	VS1003_SPI_ReadWriteByte(0x69);
	VS1003_SPI_ReadWriteByte(0x74);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	HAL_Delay(100);
	MP3_DCS(1);
}

/*******************************************************************************
* Function Name  : VS1003_RamTest
* Description    : VS1003 RAM≤‚ ‘
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003_RamTest(void)
{
	volatile uint16_t value;

	VS1003_Reset();
	VS1003_WriteReg(SPI_MODE, 0x0820);
	while(MP3_DREQ == 0);
	MP3_DCS(0);
	VS1003_SPI_ReadWriteByte(0x4d);
	VS1003_SPI_ReadWriteByte(0xea);
	VS1003_SPI_ReadWriteByte(0x6d);
	VS1003_SPI_ReadWriteByte(0x54);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	VS1003_SPI_ReadWriteByte(0x00);
	HAL_Delay(50);
	MP3_DCS(1);
	value = VS1003_ReadReg(SPI_HDAT0);
}

/*******************************************************************************
* Function Name  : VS1003_SetVol
* Description    : …Ë∂®vs1003≤•∑≈µƒ“Ù¡ø∫Õ∏ﬂµÕ“Ù
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003_SetVol(void)
{
	uint8_t i;
	uint16_t bass = 0;
	uint16_t vol = 0;
	uint8_t vset = 0;

	vset = 255 - vs1003ram[4];
	vol = vset;
	vol <<= 8;
	vol += vset;
	/* 0,henh.1,hfreq.2,lenh.3,lfreq */
	for( i = 0; i < 4; i++ )
	{
		bass <<= 4;
		bass += vs1003ram[i];
	}
	VS1003_WriteReg(SPI_BASS, bass);
	VS1003_WriteReg(SPI_VOL, vol);
}

/*******************************************************************************
* Function Name  : VS1003_WriteData
* Description    : VS1003–¥ ˝æ›
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003_WriteData(uint8_t* buf)
{
	uint8_t count = 32;

	MP3_DCS(0);
	while(count--)
	{
		VS1003_SPI_ReadWriteByte(*buf++);
	}
	MP3_DCS(1);
	MP3_CCS(1);
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
