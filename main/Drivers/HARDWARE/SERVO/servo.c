#include "servo.h"

/*******************************/
void SERVO_Init(servo *Servo, uint16_t home, int8_t OutMin, int8_t OutMax) {
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

	Servo->Min = OutMin;
  Servo->Max = OutMax;

	/******* SET HOME *******/
	TIM2->CCR2 = home; // from 45 to 115
}

/*******************************/
float SERVO_Caliration(float angle) {
	float angle_pwm=0;

	// 0 do: 75
	// 25 do: 90 -> phai
	// -25 do: 60 -> trai
	angle_pwm =  0.6 * (double)angle + 75; //from 45 to 250

	return angle_pwm;
}

/*******************************/
void SERVO_Run(servo *Servo, int8_t angle) {
	/******* Saturation *******/
	if (angle >= Servo->Max) angle=Servo->Max;
	else if (angle <= Servo->Min) angle=Servo->Min;

	/******* Calibration *******/
	Servo->PWM = SERVO_Caliration(angle);

	/******* PWM *******/
	TIM2->CCR2 = (int)Servo->PWM;
}
