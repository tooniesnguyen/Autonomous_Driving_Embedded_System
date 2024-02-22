double e,pre_e;
double current_value;
int Target_value;
double delaT; // Th?i gian l?y m?u

double kp = ...,ki =..., kd =...;

// Khai bi?n kh�u t? l?
double up;

// khai bi?n kh�u t�ch ph�n 
double ui,ui_p;
int ui_above_limit,ui_under_limit;

// khai bi?n kh�u d?o h�m
double ud,udf,udf_p;
double alpha; // H? s? b? l?c

// khai bi?n output
double u;
int u_above_limit,u_under_limit;
int dir,pwm,pwm_movable;

void PID(){
	
	// kho?ng c?n d�p ?ng c?a h? th?ng
	e = Target_value - current_value;

	// Kh�u t? l? 
	up = kp*e;
	
	// kh�u t�ch ph�n
	ui = ui_p + ki*e*deltaT;
	// B�o h�a kh�u t�ch ph�n
	if (ui>ui_above_limit)ui=ui_above_limit;
	else if(ui<ui_under_limit)ui=ui_under_limit;	

	// kh�u d?o h�m
	ud = kd*(e - pre_e)/deltaT;
	// L?c th�ng th?p kh�u d?o h�m 
	udf = (1-alpha)*udf_p+alpha*ud;
	
	pre_e = e;
	ui_p = ui;
	udf_p = udf;

	// T?ng out put
	u = up + udf+ui;
	// B�o h�a output
	if(u>u_above_limit)u = u_above_limit;
	else if (u<u_under_limit)u=u_under_limit;
	
	// X�c d?nh chi?u:
	if (u>0)dir=-1;
	else if(u<0)dir = 1;
	else dir = 0;
	
	// Xu?t gi� tr? pwm
	pwm = abs(u);
	if ((pwm<pwm_movable)&&(e!=0)){
		pwm = pwm_movable;

	}
}
