# Interface BLDC motor with STM32
> :warning: Warning: This guide is for the stm32 chip `Nucleo F40RE` code. If you are using stm32 with another code, please be sure to configure it correctly according to your code line, otherwise the chip will be locked.

### Step 1: Config CubeMx
- Choose chip: Open `CubeMx`  -> `ACCESS TO MCU SELECTOR` -> `Commerial Part Number: STM32F401RET6`
- Clock Config: 
  - `Pinout & Configuration` -> `System Core` -> `RCC` -> `High Speed Clock (HSE)` -> `Crystal/Ceramic Resonator`
  - `Clock Configuration`
<br><img src="..\images\clock_config.png" width="80%" height="80%"> </br> 

- Timer Config: `Pinout & Configuration` -> `Timers` -> `TIM4`
  - Tick `Internal Clock`
  - `Parameter Settings` -> `Prescaler: 84-1`, `Counter Period: 1000-1`
  - `NVCC Settings` -> Tick `Enable` `TIM4 global interrupt`
<br><img src="..\images\esc_clock.png" width="80%" height="80%"> </br>




- USART2 Config: `Pinout & Configuration` -> `Connectivity`
  - `Mode` -> `Asynchronous`
  - `DMA Settings` -> `Add` -> `DMA Request: USART2_RX`


### Step 2: Code on CubeIDE
- Open `main.c` and add

```

...
/* USER CODE BEGIN Includes */
#include "string.h"
/* USER CODE END Includes */
...

/* USER CODE BEGIN 0 */
#define RxBuf_SIZE 10
#define MainBuf_SIZE 20

uint8_t RxBuf[RxBuf_SIZE];
uint8_t MainBuf[MainBuf_SIZE];



uint8_t data[2000] = "Hello worlds 3 \n";




void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{

	if (huart->Instance == USART2)
	{
		memcpy(MainBuf, RxBuf, Size);
		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *) RxBuf, RxBuf_SIZE);
//		__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
	}

}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_UART_Transmit_IT(&huart2, data, 50);
}
/* USER CODE END 0 */
...

  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_UARTEx_ReceiveToIdle_DMA(&huart2, RxBuf, RxBuf_SIZE);
  __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
  /* USER CODE END 2 */
....

```

- Complie and Run code:
<br><img src="..\images\compile.png" width="100%" height="100%"> </br> 

### References
- https://controllerstech.com/uart-receive-in-stm32/
- https://controllerstech.com/uart-transmit-in-stm32/
- https://embeddedthere.com/stm32-timer-tutorial-using-interrupt/