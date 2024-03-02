# Bosch BNO055 gyro library for STM32
> :warning: Warning: This guide is for the stm32 chip `Nucleo F40RE` code. If you are using stm32 with another code, please be sure to configure it correctly according to your code line, otherwise the chip will be locked.

### Step 1: Config CubeMx
- Choose chip: Open `CubeMx`  -> `ACCESS TO MCU SELECTOR` -> `Commerial Part Number: STM32F401RET6`
- Enable I2C: `Pin & Configuration` -> `Connectivity` -> `I2C1` -> `I2C`
    - `Parameter Settings` -> `I2C Speed Mode` -> `Fast Mode`
<br><img src="..\images\config_bno.png" width="100%" height="100%"> </br>  

- Code Generate: `Project Manager`  
  - `Project Name: {name_folder}`
  - `Project Location` Change the folder address if you want
  - `Toolchain / IDE` -> `STM32CubeIDE`
  - Press -> `GENERATE CODE`

### Step 2: Code on CubeIDE
- Down three file ([bno055_stm32.h](./bno055_stm32.h), [bno055.c](./bno055.c), [bno055.h](./bno055.h)) to folder `src` and `Inc` to your project. Example, you need to copy header files to ./Core/Inc and bno055.c to ./Core/Src and then add file with right click on Application -> User -> Core in project tree and Add -> Add files ... (select bno055.c).


## WORK IN PROGRESS

There are no libraries to use BNO055 with STM32.
We created one to use with STM32 HAL I2C.

It does support FreeRTOS, see `bno055.h`. Uncomment `#define FREERTOS_ENABLED` to enable FreeRTOS.

## Usage

Use CubeMX to init i2c in fast mode.

Copy `bno055.c`, `bno055.h` and `bno055_stm32.h` to your project.

Set BNO055 i2c address in `bno055.h`

```c
#define BNO055_I2C_ADDR    BNO055_I2C_ADDR_LO    // For 0x28
#define BNO055_I2C_ADDR    BNO055_I2C_ADDR_HI    // For 0x29
```

Include `bno055_stm32.h`.
Pass i2c handler to bno055_assignI2C function and set work mode:

```c
bno055_assignI2C(&hi2c1);
bno055_setup();
bno055_setOperationModeNDOF();
```

Then use bno055_getVectorEuler to receive euler angle data:

```c
bno055_vector_t v = bno055_getVectorEuler();
printf("Heading: %.2f Roll: %.2f Pitch: %.2f\r\n", v.x, v.y, v.z);
```

Or use bno055_getVectorQuaternion to receive quaternion data:

```c
bno055_vector_t v = bno055_getVectorQuaternion();
printf("W: %.2f X: %.2f Y: %.2f Z: %.2f\r\n", v.w, v.x, v.y, v.z);
```

To remap axis, use bno055_setAxisMap in config mode (refer to datasheet page 24):

```c
bno055_axis_map_t axis = {
  .x = BNO055_AXIS_X,
  .x_sign = BNO055_AXIS_SIGN_POSITIVE,
  .y = BNO055_AXIS_Y,
  .y_sign = BNO055_AXIS_SIGN_POSITIVE,
  .z = BNO055_AXIS_Z,
  .z_sign = BNO055_AXIS_SIGN_POSITIVE
};
bno055_setAxisMap(axis);
```

### Full example

```c
...
/* USER CODE BEGIN Includes */
#include "bno055_stm32.h"
/* USER CODE END Includes */

...
  /* USER CODE BEGIN 2 */
  bno055_assignI2C(&hi2c1);
  bno055_setup();
  bno055_setOperationModeNDOF();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    bno055_vector_t v = bno055_getVectorEuler();
    printf("Heading: %.2f Roll: %.2f Pitch: %.2f\r\n", v.x, v.y, v.z);
    v = bno055_getVectorQuaternion();
    printf("W: %.2f X: %.2f Y: %.2f Z: %.2f\r\n", v.w, v.x, v.y, v.z);
    HAL_Delay(1000);
    /* USER CODE END WHILE */
  }
...

```

### Output

```
Heading: 292.81 Roll: 50.00 Pitch: 175.62
W: 0.35 X: 0.45 Y: -0.78 Z: 0.23
Heading: 292.81 Roll: 50.00 Pitch: 175.62
W: 0.35 X: 0.45 Y: -0.78 Z: 0.23
```

- Complie and Run code:
<br><img src="..\images\compile.png" width="100%" height="100%"> </br> 


### References:
- https://www.ivyknob.com/blog/bno055-gyro-library-for-stm32/
- https://github.com/ivyknob/bno055_stm32