/*
 * macro.h
 *
 *  Created on: Oct 27, 2022
 *      Author: efmgh
 */

#ifndef INC_MACRO_H_
#define INC_MACRO_H_

#define GYRO_A 0x01
#define GYRO_B 0x02
#define GYRO_C 0x04
#define GYRO_D 0x08
#define GYRO_E 0x10

#define TIM05 0.5		//mm
#define TIM005 0.05 	//mm

#define TIRE 14.0

#define ADC_SENS 5

#define MAX_SPEED 2.5
#define MIN_SPEED 1.8
#define ACC 5

#define CM_COUNT 1200

double Speed_Ref;
double coe;

int Crossing_Flag;


#endif /* INC_MACRO_H_ */
