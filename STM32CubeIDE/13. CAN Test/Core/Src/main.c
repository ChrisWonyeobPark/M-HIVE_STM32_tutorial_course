/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "lwip.h"
#include "sdio.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CLCD.h"
#include "7seg.h"
#include "VS1003.h"
#include "mp3sample.h"
#include "udp_echoserver.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t rx3_data;
uint8_t SW1_flag = 0;
uint8_t SW2_flag = 0;
uint8_t SW3_flag = 0;
uint8_t SW4_flag = 0;
volatile uint8_t can1_rx0_flag = 0;
extern uint8_t udp_data;
extern uint8_t udp_flag;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int _write(int file, char* p, int len)
{
	HAL_UART_Transmit(&huart3, p, len, 10);
	return len;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	volatile uint16_t adcval[4];
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_TIM7_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM10_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  MX_LWIP_Init();
  MX_CAN1_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

	HAL_UART_Receive_IT(&huart3, &rx3_data, 1);
	HAL_TIM_Base_Start_IT(&htim7);

	CLCD_GPIO_Init();
	CLCD_Init();
	CLCD_Puts(0, 0, "Welcome to");
	CLCD_Puts(0, 1, "M-HIVE");
	CLCD_Clear();

	_7SEG_GPIO_Init();

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);

	HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);

//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);

	HAL_ADC_Start_DMA(&hadc1, &adcval[0], 4);
//	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

	TIM10->CCR1 = 1500;


	TIM5->CCR1 = 0;
	TIM5->CCR4 = 5000;

	TIM7->PSC = 9;

	VS1003_Init();
	VS1003_SoftReset();

	  /* tcp echo server Init */
	  udp_echoserver_init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint8_t a = 0;
	float f = 1.234;
	uint8_t str[20];
	uint16_t ccr = 0;
	uint16_t psc = 1000;
	uint8_t ud_flag = 0;
	uint16_t dacval = 0;
	uint8_t eeprom[10];// = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};

	//HAL_I2C_Mem_Write(&hi2c1, 0xA0, 0x00, I2C_MEMADD_SIZE_8BIT, &eeprom[0], 10, 10);

	HAL_Delay(3);

	for(int i = 0;i<10;i++) eeprom[i] = 0x00;

	HAL_I2C_Mem_Read(&hi2c1, 0xA0, 0x00, I2C_MEMADD_SIZE_8BIT, &eeprom[0], 10, 10);

	sprintf(str, "%02x %02x %02x %02x %02x", eeprom[0], eeprom[1], eeprom[2], eeprom[3], eeprom[4]);
	CLCD_Puts(0, 0, str);
	sprintf(str, "%02x %02x %02x %02x %02x", eeprom[5], eeprom[6], eeprom[7], eeprom[8], eeprom[9]);
	CLCD_Puts(0, 1, str);

	int i = 0;

	BYTE buf[32] = "Hello world";	// file copy buffer
	uint32_t bw, br;
	/************* 1. "0:/" drive mount ***********/
	if((retSD = f_mount(&SDFatFS, &SDPath[0], 1)) == FR_OK)
	{
		sprintf(str, "f_mount OK %d", retSD);
		CLCD_Puts(0, 0, str);
	}
	else
	{
		sprintf(str, "f_mount failed %d", retSD);
		CLCD_Puts(0, 0, str);
	}
	/*****************************************************/

//	/*********** 2. create and write to a file ***********/
//	if((retSD = f_open(&SDFile, "0:/M-HIVE.txt", FA_CREATE_NEW | FA_WRITE)) == FR_OK)
//	{
//		sprintf(buf, "Hello world");
//		f_write(&SDFile, buf, sizeof(buf), &bw);
//
//		sprintf(str, "%d bytes", bw);
//		CLCD_Puts(0, 0, str);
//
//		f_close(&SDFile);
//	}
//	else
//	{
//		sprintf(str, "error %d\n", retSD);
//		CLCD_Puts(0, 0, str);
//	}
//	/*****************************************************/

//	/********** 3. open and read from a file  ************/
//	if((retSD = f_open(&SDFile, "0:/ChrisP.txt", FA_OPEN_EXISTING | FA_READ)) == FR_OK)
//	{
//		CLCD_Clear();
//
//		f_read(&SDFile, buf, 32, &br);
//		sprintf(str, "%s", buf);
//		CLCD_Puts(0, 0, str);
//
//		sprintf(str, "%d bytes", br);
//		CLCD_Puts(0, 1, str);
//	}
//	else
//	{
//		sprintf(str, "open error %d\n", retSD);
//		CLCD_Puts(0, 0, str);
//	}
//	/*****************************************************/

	/*************** read directory info  ****************/
	DIR dir;
	FILINFO filinfo;
	uint16_t filecnt = 0;
	if((retSD = f_opendir(&dir, "0:/")) == FR_OK) // (0:/) ?ï¿½ï¿½?ï¿½ï¿½ ?ï¿½ï¿½?ï¿½ï¿½?ï¿½ï¿½ dir?ï¿½ï¿½ ï¿?? ?ï¿½ï¿½ë³´ï¿½?? ???ï¿½ï¿½
	{
		while(1) // ?ï¿½ï¿½?ï¿½ï¿½ ï¿???ï¿½ï¿½ ?ï¿½ï¿½ï¿??
		{
			retSD = f_readdir(&dir, &filinfo); //?ï¿½ï¿½?ï¿½ï¿½?ï¿½ï¿½ï¿?? ?ï¿½ï¿½?ï¿½ï¿½ ?ï¿½ï¿½?ï¿½ï¿½?ï¿½ï¿½ï¿?? ?ï¿½ï¿½?ï¿½ï¿½ ?ï¿½ï¿½ï¿??. ?ï¿½ï¿½?ï¿½ï¿½ ?ï¿½ï¿½?ï¿½ï¿½ï¿?? ï¿?? ?ï¿½ï¿½?ï¿½ï¿½?ï¿½ï¿½?ï¿½ï¿½ï¿?? ?ï¿½ï¿½?ï¿½ï¿½ï¿??.
			if(dir.sect == 0) break; //?ï¿½ï¿½?ï¿½ï¿½?ï¿½ï¿½ ?ï¿½ï¿½?ï¿½ï¿½ ?ï¿½ï¿½?ï¿½ï¿½?ï¿½ï¿½ ?ï¿½ï¿½?ï¿½ï¿½ ê²½ìš°

			printf("%s\t0x%x\n", filinfo.fname, filinfo.fattrib);
			filecnt++;
		}
		printf("\nTotal %d file(s)..\n\n", filecnt);
	}
	else
	{
		printf("The file/directory object is invalid! %d\n", retSD);
	}
	/*****************************************************/

	/****************** open a file **********************/
	unsigned char filename[20] = "0:/1.mp3";
	uint16_t index = 0;

	if((retSD = f_open(&SDFile, filename, FA_OPEN_EXISTING | FA_READ)) == FR_OK)
	{
		CLCD_Clear();
		sprintf(str, "%s opened", filename);
		CLCD_Puts(0, 0, str);
	}
	else
	{
		sprintf(str, "open error %d\n", retSD);
		CLCD_Puts(0, 0, str);
	}
	/*****************************************************/

	uint8_t pp_flag = 0;

	canFilter1.FilterMaskIdHigh = 0x7F3 << 5;
	canFilter1.FilterIdHigh = 0x106 << 5;
	canFilter1.FilterMaskIdLow = 0x7F3 << 5;
	canFilter1.FilterIdLow = 0x106 << 5;
	canFilter1.FilterMode = CAN_FILTERMODE_IDMASK;
	canFilter1.FilterScale = CAN_FILTERSCALE_16BIT;
	canFilter1.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	canFilter1.FilterBank = 0;
	canFilter1.FilterActivation = ENABLE;

	HAL_CAN_ConfigFilter(&hcan1, &canFilter1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_CAN_Start(&hcan1);

  while (1)
  {
	  if(can1_rx0_flag)
	  {
		  can1_rx0_flag = 0;

		  CLCD_Clear();
		  sprintf(str, "Rx ID:   0x%3X", canRxHeader.StdId);
		  CLCD_Puts(0, 0, str);
		  sprintf(str, "Rx Data: 0x%2X", can1Rx0Data[0]);
		  CLCD_Puts(0, 1, str);
	  }

	  if(SW1_flag)
	  {
		  SW1_flag = 0;

		  canTxHeader.StdId = 0x102;
		  canTxHeader.RTR = CAN_RTR_DATA;
		  canTxHeader.IDE = CAN_ID_STD;
		  canTxHeader.DLC = 8;

		  for(int i=0;i<8;i++) can1Tx0Data[i]++;

		  TxMailBox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);
		  HAL_CAN_AddTxMessage(&hcan1, &canTxHeader, &can1Tx0Data[0], &TxMailBox);
	  }

	  if(SW2_flag)
	  {
		  SW2_flag = 0;

		  canTxHeader.StdId = 0x106;
		  canTxHeader.RTR = CAN_RTR_DATA;
		  canTxHeader.IDE = CAN_ID_STD;
		  canTxHeader.DLC = 8;

		  for(int i=0;i<8;i++) can1Tx0Data[i]++;

		  TxMailBox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);
		  HAL_CAN_AddTxMessage(&hcan1, &canTxHeader, &can1Tx0Data[0], &TxMailBox);
	  }

	  if(SW3_flag)
	  {
		  SW3_flag = 0;

		  canTxHeader.StdId = 0x10A;
		  canTxHeader.RTR = CAN_RTR_DATA;
		  canTxHeader.IDE = CAN_ID_STD;
		  canTxHeader.DLC = 8;

		  for(int i=0;i<8;i++) can1Tx0Data[i]++;

		  TxMailBox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);
		  HAL_CAN_AddTxMessage(&hcan1, &canTxHeader, &can1Tx0Data[0], &TxMailBox);
	  }

	  if(SW4_flag)
	  {
		  SW4_flag = 0;

		  canTxHeader.StdId = 0x10E;
		  canTxHeader.RTR = CAN_RTR_DATA;
		  canTxHeader.IDE = CAN_ID_STD;
		  canTxHeader.DLC = 8;

		  for(int i=0;i<8;i++) can1Tx0Data[i]++;

		  TxMailBox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);
		  HAL_CAN_AddTxMessage(&hcan1, &canTxHeader, &can1Tx0Data[0], &TxMailBox);
	  }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3)
	{
		HAL_UART_Receive_IT(&huart3, &rx3_data, 1);
		HAL_UART_Transmit(&huart3, &rx3_data, 1, 10);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static unsigned short cnt = 0;
	if(htim->Instance == TIM7)
	{
//		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (sinf(2 * 3.1415926535f * 100 * cnt / 1000.f) + 1) * 2047);
		cnt++;
		if(cnt > 999) cnt = 0;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_3)
	{
		SW1_flag = 1;
	}

	if(GPIO_Pin == GPIO_PIN_15)
	{
		SW2_flag = 1;
	}

	if(GPIO_Pin == GPIO_PIN_4)
	{
		SW3_flag = 1;
	}

	if(GPIO_Pin == GPIO_PIN_10)
	{
		SW4_flag = 1;
	}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == CAN1)
	{
		HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &canRxHeader, &can1Rx0Data[0]);
		can1_rx0_flag = 1;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
