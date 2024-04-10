#ifndef __UTE_AI_H__
#define __UTE_AI_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************/
#include "stm32f4xx_hal.h"
#include "math.h"

#define Lw 57 // Chieu dai xe
#define dw 31 // Chieu ngang xe
#define V_PI (double)3.14159265358979323846

#include "ESC/esc.h"
#include "SERVO/servo.h"

/*****************/
void Run(esc *Esc, servo *Servo, int16_t speed, int8_t angle);

/*****************/
#ifdef __cplusplus
}
#endif
#endif
