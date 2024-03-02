# Interface BLDC motor with STM32
> :warning: Warning: This guide is for the stm32 chip `Nucleo F40RE` code. If you are using stm32 with another code, please be sure to configure it correctly according to your code line, otherwise the chip will be locked.

### Step 1: Config CubeMx
- Choose chip: Open `CubeMx`  -> `ACCESS TO MCU SELECTOR` -> `Commerial Part Number: STM32F401RET6`
- Clock Config: 
  - `Pinout & Configuration` -> `System Core` -> `RCC` -> `High Speed Clock (HSE)` -> `Crystal/Ceramic Resonator`
  - `Clock Configuration`
<br><img src="..\images\clock_config.png" width="80%" height="80%"> </br> 

- Timer Config: `Pinout & Configuration` -> `Timers` -> `TIM3`
  - `Channel2: PWM Generation CH2`
  - `Parameter Settings` -> `Prescaler: 1680-1`, `Counter Period: 1000-1`
<br><img src="..\images\servo_config.png" width="80%" height="80%"> </br> 

- Code Generate: `Project Manager`  
  - `Project Name: {name_folder}`
  - `Project Location` Change the folder address if you want
  - `Toolchain / IDE` -> `STM32CubeIDE`
  - Press -> `GENERATE CODE`

### Step 2: Code on CubeIDE
- Open `main.c` and add

```
...
/* USER CODE BEGIN 0 */
int pwm = 24;
/* USER CODE END 0 */
...

  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  /* USER CODE END 2 */

...

  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // The pwm range (18 24 29) <=> (-25 0 25) degree
	  htim3.Instance->CCR2 = pwm;
    /* USER CODE END WHILE */
...

```

- Complie and Run code:
<br><img src="..\images\compile.png" width="100%" height="100%"> </br> 


### References
- https://controllerstech.com/servo-motor-with-stm32/