/*
 * LineTrace.c
 *
 *  Created on: Oct 27, 2022
 *      Author: efmgh
 */

#include "LineTrace.h"

void Trace_Init()
{
	Time = Start_Flag = 0;
	Speed_Ref = 0;
}

void TraceDebug()
{
	//printf("L -> %f, R -> %f\r\n", Speed_input_L, Speed_input_R);
	//printf("L -> %0.2f, R -> %0.2f, S -> %0.2f\r\n", Line_Calib_L, Line_Calib_R, Stear_Sens);
	//printf("ADC -> %f, theta -> %f, degree -> %f, R -> %f, T -> %f\r\n", Stear_Sens, theta, degree, Turning_Radius, tread);
	//printf("SL -> %0.5f, SR -> %0.5f\r\n", Speed_L(), Speed_R());
	//printf("%f	%f	%f	%f\r\n", Speed_L(), Speed_R(), Gyro, Score_Time);
	//printf("%d\r\n", );
}

void LineTrace(uint8_t motor_flag, uint8_t memory_flag)
{

	theta = 2 * M_PI * ( ( 2097 - (double)Stear_Sens ) / 4096 );
	degree = theta * ( 180. / M_PI );
	Turning_Radius = 40.1 / tan(theta);

	//tread = 54.142 - (0.0121 * labs(Turning_Radius)) - (1.91e5 * Turning_Radius * Turning_Radius);
	//tread = 93.502 * pow( labs(Turning_Radius), -0.1326 );
	tread = (54.78 - (0.0246 * labs(Turning_Radius))) * (MIN_SPEED / Speed_Ref);
	if(tread >= 54.25) tread = 54.25;
	if(Speed_Ref <= MIN_SPEED && tread <= 40) tread = 40;
	else if(Speed_Ref > MIN_SPEED && tread <= 5) tread = 5;

	Speed_input_R = SpeedContorol_R( (Turning_Radius - tread) * (Speed_Ref / Turning_Radius) );
	Speed_input_L = SpeedContorol_L( (Turning_Radius + tread) * (Speed_Ref / Turning_Radius) );

	switch(motor_flag){
		case 0:
			motor_R(0);
			motor_L(0);
			motor_S(0);
			Calculate_Mileage(0);
			break;
		case 1:
			motor_R( Speed_input_R );
			motor_L( Speed_input_L );
			motor_S( StearingContorol( Line_Calib_R - Line_Calib_L ) );
			Time++;
			Calculate_Mileage(0);
			if(Time >= 5000) Speed_Ref = 0.7;
			else Speed_Ref = 0.0;
			break;
		case 2:
			motor_R( Speed_input_R );
			motor_L( Speed_input_L );
			motor_S( StearingContorol( Line_Calib_R - Line_Calib_L ) );
			Speed_Ref = Calculate_Mileage(memory_flag);
			break;
		case 3:
			motor_R( Speed_input_R );
			motor_L( Speed_input_L );
			motor_S( StearingContorol( Line_Calib_R - Line_Calib_L ) );
			Speed_Ref -= 0.002;
			if(Speed_Ref <= 0) Speed_Ref = 0.0;
			break;
	}

}
