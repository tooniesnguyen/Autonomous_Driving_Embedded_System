#include "pid.h"

double kp_compute, ki_compute, kd_compute;
/*********************/
void PID_Init(pid *PID,
              float T,
              float Kp,
              float Ki,
              float Kd,
							float OutMin,
              float OutMax) {
	PID->T = T;
								
	PID->Output.Min = OutMin;
  PID->Output.Max = OutMax;

  PID->Kp = Kp;
  PID->Ki = Ki;
  PID->Kd = Kd;								
}

/*************************/
float PID_Process(pid *PID,
                  float Setpoint,
                  float CurrentPoint) {
										
  PID->Error = Setpoint - CurrentPoint;
	
	/***************** AdaptiveTunings *****************/
	kp_compute = PID->Kp;
	ki_compute = PID->Ki;
	kd_compute = PID->Kd;										
//  if (fabs(PID->Error) < 20) {
//		kp_compute = 0.1;
//		ki_compute = 0.01;
//		kd_compute = 0.01;
//	}
//	else {
//		kp_compute = PID->Kp;
//		ki_compute = PID->Ki;
//		kd_compute = PID->Kd;
//	}
	
	/***************** Compute *****************/					
	PID->pPart = kp_compute * PID->Error;
	PID->dPart = kd_compute * (PID->Error-PID->pre_Error);//*1000/PID->T;
	PID->iPart += ki_compute * PID->Error;// * PID->T/1000;
	PID->Output.Current += PID->pPart + PID->iPart + PID->dPart;

  PID->pre_Error = PID->Error;
	
	/***************** Saturation *****************/
	if (Setpoint > 0) {
		if (PID->Output.Current <= 0)	PID->Output.Current=0;
	}
	else if (Setpoint == 0) {
		PID->Output.Current = 0;
	}
	else {
		if (PID->Output.Current >= 0) PID->Output.Current=0;
	}
	
//	if (PID->Output.Min != 0) {
//		if (0 < PID->Output.Current && PID->Output.Current < PID->Output.Min) {
//			PID->Output.Current = PID->Output.Min;
//		}
//		else if (-PID->Output.Min < PID->Output.Current && PID->Output.Current < 0) {
//			PID->Output.Current = -PID->Output.Min;
//		}
//	}

	if (PID->Output.Max != 0) {
		if (PID->Output.Max < PID->Output.Current) {
			PID->Output.Current = PID->Output.Max;
		}
		else if (PID->Output.Current < (-PID->Output.Max)) {
			PID->Output.Current = -PID->Output.Max;
		}
	}
	
	return PID->Output.Current;
}

/**********************/
void PID_Reset(pid *PID) {
  PID->Error = 0;
  PID->Output.Current = 0;
  PID->pre_Error = 0;
}
