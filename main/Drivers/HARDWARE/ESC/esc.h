#ifndef __ESC_H__
#define __ESC_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/***************/
#include "main.h"
#include "tim.h"
#include "stdlib.h"     /* abs */

	/*****************/
#include "stm32f4xx_hal.h"
#include "math.h"

#define Lw 57 // Chieu dai xe
#define dw 31 // Chieu ngang xe
#define V_PI (double)3.14159265358979323846

/*****************/
typedef struct {
	int16_t Max, Min;
	float Set;
	float Output;
} esc;

/*****************/
//extern velocity Velocity;

/**************************/
void ESC_Init(esc *Esc, uint16_t home, int16_t OutMin, int16_t OutMax);
void ESC_Run(esc *Esc, float speed);

/*****************/
#ifdef __cplusplus
}
#endif
#endif
