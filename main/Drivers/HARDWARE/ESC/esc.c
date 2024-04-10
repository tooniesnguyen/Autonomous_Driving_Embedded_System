#include "esc.h"
#include "main.h"

/*******************************/
double T=0.1;

/*******************************/
extern htim3;

void ESC_Init(esc *Esc, uint16_t home, int16_t OutMin, int16_t OutMax) {

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

	Esc->Min = OutMin;
  Esc->Max = OutMax;

	/******* SET HOME *******/
	Esc->Output = home;
	TIM3->CCR2 = home;
}

/************************/
void Acceleration(float V_want, float *vout, float _acc, float _dcc) {
	if(fabs(*vout) < fabs(V_want)) {
    *vout += _acc*T;
		if(fabs(*vout) >= fabs(V_want)) *vout = V_want;
   }
  if(fabs(*vout) > fabs(V_want)) {
     *vout -= _dcc*T;
		if (_dcc >= 0) {
			if(*vout <= V_want) *voutS = V_want;
		}
		else if(*vout >= V_want) *vout = V_want;
  }
}

float ESC_Caliration(float speed) {
	float esc_speed;

	esc_speed =  0.5 * (double)speed + 100; // 65 (reverse) - 100 (stop) - 235 (drive)

	return esc_speed;
}

/************************/
void ESC_Run(esc *Esc, float speed) {
	float acc = 10, dcc = 10;

	/******* Saturation *******/
	if (speed >= Esc->Max) speed=Esc->Max;
	else if (speed <= Esc->Min) speed=Esc->Min;

	/******* Calibration *******/
	Esc->Set = ESC_Caliration(speed);

	/******* Processing *******/
	if (Esc->Set > 0) Acceleration(Esc->Set, &Esc->Output, acc, dcc);
	else if (Esc->Set < 0) Acceleration(Esc->Set, &Esc->Output, -acc, -dcc);
	else {
		if (Esc->Output < 0) Acceleration(Esc->Set, &Esc->Output, -acc, -dcc);
		else Acceleration(Esc->Set, &Esc->Output, acc, dcc);
	}

	/******* PWM *******/
	TIM3->CCR2 = (int)Esc->Output;
}
