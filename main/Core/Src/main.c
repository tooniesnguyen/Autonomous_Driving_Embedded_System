/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdbool.h"

/******* HARDWARE *******/
#include "ESC/esc.h"
#include "SERVO/servo.h"
#include "IMU/bno055_stm32.h"

/******* SOFTWARE *******/
#include "CONTROLLER/ute_ai.h"
#include "FUNCTIONS/math_functions.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
esc Esc;
servo Servo;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t rxdata[4] = {0, 0, 0, 0};
int16_t receive_speed;
int8_t receive_angle;
uint8_t flag_button=0;
extern DMA_HandleTypeDef hdma_usart2_rx;
bno055_vector_t v;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	/*************** ESC ***************/
	ESC_Init(&Esc, 100, -10, 25);
//	TIM3->CCR2 = 100;

	/************** SERVO **************/
	SERVO_Init(&Servo, 75, -25, 25);
//	TIM2->CCR2 = 90;

	/*************** IMU ***************/
	  bno055_assignI2C(&hi2c1);
	  bno055_setup();
	  bno055_setOperationModeNDOF();

	/************** TIMER **************/
	HAL_TIM_Base_Start_IT(&htim1);

	/************** COMMUNICATION **************/
	while (HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxdata, 4) != HAL_OK) HAL_UART_DMAStop(&huart2);
	__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	    v = bno055_getVectorQuaternion();
	    HAL_Delay(100);
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
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint16_t i = 100;

/*********************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM1) {
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

		/************* SETUP ESC *************/
//		TIM3->CCR2 = i;
//		// Tang
//		if (i<=105) i+=1;
			// Giam
//		if (i>=100) i-=1;
		/*************************************/

		/************* Control *************/
//		Run(&Esc, &Servo, -10, 0);
		if (flag_button == 0) Run(&Esc, &Servo, 0, 0); // Speed, Angle
		else Run(&Esc, &Servo, receive_speed, receive_angle);  // Run(&Esc, &Servo, -10, 0); // Speed, Angle
		}
}

/*********************************************************/
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
  if (huart->Instance == USART2) {
	  while (HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxdata, 4) != HAL_OK) HAL_UART_DMAStop(&huart2);
    __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
		if (Size == 4) {
			if (rxdata[3] == 25) {
				receive_speed = ((int16_t)rxdata[1]<<8)|rxdata[0];
				receive_angle = rxdata[2];
			}
			else {
				receive_speed = 0;
				receive_angle = 0;
			}

			/**** CHECK DATA ****/
//			if (receive_speed == 100 && receive_angle == 0) HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//			else HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		}
  }
}

/*********************************************************/
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART2) {
		while (HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxdata, 4) != HAL_OK) HAL_UART_DMAStop(&huart2);
    __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
	}
}

/************************SETUP ESC************************/
uint16_t setup_pwm;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == STOP_Button_Pin) {
		flag_button=0;
//		setup_pwm = 65; //65 (100Hz) - 35 (50Hz)
//		TIM3->CCR2 = setup_pwm;
	}
	else if (GPIO_Pin == FUNC_Button_Pin) {
		flag_button=1;
//		setup_pwm = 100; // 150 (100Hz) - 75 (50Hz)
//		TIM3->CCR2 = setup_pwm;
	}
	else if (GPIO_Pin == START_Button_Pin) {
		flag_button=2;
//		setup_pwm = 235; // 235 (100Hz) - 115 (50Hz)
//		TIM3->CCR2 = setup_pwm;
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
