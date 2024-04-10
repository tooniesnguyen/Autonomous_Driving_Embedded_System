#ifndef __MATH_FUNCTIONS_H__
#define __MATH_FUNCTIONS_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/************************/
#include "stm32f4xx_hal.h"
/****************/
#include "math.h"

/*************************************/

#define PI		(float)3.14159265358979
#define RADS 	(PI / (float)180)
#define DEGS 	((float)180 / PI)

// Trigonometry using degrees
#define SIND(value) sin((value) * RADS)
#define COSD(value) cos((value) * RADS)
#define TAND(value) tan((value) * RADS)

#define ACOSD(value) (acos((value)) * DEGS);
#define ATAND(value) (atan((value)) * DEGS);

/**********************************************/

float map(float Value, float InputMin, float InputMax, float OutputMin, float OutputMax);

/*****************/
#ifdef __cplusplus
}
#endif
#endif
