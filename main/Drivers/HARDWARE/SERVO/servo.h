#ifndef __SERVO_H__
#define __SERVO_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/***************/
#include "main.h"
#include "tim.h"

/*****************/
typedef struct {
	int8_t Max, Min;
	float PWM;
} servo;

/**************************/
void SERVO_Init(servo *Servo, uint16_t home, int8_t OutMin, int8_t OutMax);
void SERVO_Run(servo *Servo, int8_t angle);

/*****************/
#ifdef __cplusplus
}
#endif
#endif
