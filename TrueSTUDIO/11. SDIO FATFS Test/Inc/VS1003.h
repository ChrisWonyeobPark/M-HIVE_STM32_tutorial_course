/****************************************Copyright (c)****************************************************
**
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               VS1003.h
** Descriptions:            The VS1003 application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2011-2-17
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             ChrisP (cafe.naver.com/mhiveacademy, https://www.youtube.com/wonyeobchrispark)
** Modified date:           2018-6-2
** Version:                 V2.0
** Descriptions:            HAL Driver version
**
*********************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _HAL_VS1003B_H
#define _HAL_VS1003B_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define SPI_SPEED_HIGH    1
#define SPI_SPEED_LOW     0

/* reset */
#define MP3_RESET(x)	x ? HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)

/* /CS */
#define MP3_CCS(x)		x ? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)

/* xDCS */
#define MP3_DCS(x)		x ? HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)

/* DREQ */
#define MP3_DREQ		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)

#define VS1003_WRITE_COMMAND	0x02
#define VS1003_READ_COMMAND		0x03

/* VS1003 Register */
#define SPI_MODE        	0x00
#define SPI_STATUS      	0x01
#define SPI_BASS        	0x02
#define SPI_CLOCKF      	0x03
#define SPI_DECODE_TIME 	0x04
#define SPI_AUDATA      	0x05
#define SPI_WRAM        	0x06
#define SPI_WRAMADDR    	0x07
#define SPI_HDAT0       	0x08
#define SPI_HDAT1       	0x09
#define SPI_AIADDR      	0x0a
#define SPI_VOL         	0x0b
#define SPI_AICTRL0     	0x0c
#define SPI_AICTRL1     	0x0d
#define SPI_AICTRL2     	0x0e
#define SPI_AICTRL3     	0x0f
#define SM_DIFF         	0x01
#define SM_JUMP         	0x02
#define SM_RESET        	0x04
#define SM_OUTOFWAV     	0x08
#define SM_PDOWN        	0x10
#define SM_TESTS        	0x20
#define SM_STREAM       	0x40
#define SM_PLUSV        	0x80
#define SM_DACT         	0x100
#define SM_SDIORD       	0x200
#define SM_SDISHARE     	0x400
#define SM_SDINEW       	0x800
#define SM_ADPCM        	0x1000
#define SM_ADPCM_HP     	0x2000

/* Private function prototypes -----------------------------------------------*/
void VS1003_Init(void);
void VS1003_Reset(void);
void VS1003_SoftReset(void);
void HAL_VS1003_SPI_Init(void);
void VS1003_SetVol(void);
void VS1003_RamTest(void);
void VS1003_SineTest(void);
void VS1003_Record_Init(void);
void VS1003_ResetDecodeTime(void);
uint16_t VS1003_GetDecodeTime(void);
void VS1003_WriteData( uint8_t * buf);
void VS1003_WriteReg( uint8_t reg,uint16_t value );
uint16_t VS1003_ReadReg( uint8_t reg);


#endif /* _HAL_VS1003B_H */
