/*
 * speed.h
 *
 *  Created on: 2022/10/28
 *      Author: efmgh
 */

#ifndef INC_SPEED_H_
#define INC_SPEED_H_

#include "motor.h"
#include "macro.h"
#include "Accelerometer.h"

#include <math.h>

double speedR_I_buff, speedL_I_buff, stear_I_buff, stear_D_buff, stear_buff;

//banquet art
double banquet_I_buff, banquet_D_buff, banquet_buff;

double SpeedContorol_R(double);
double SpeedContorol_L(double);
double StearingContorol(double);

double banquet_art();

#endif /* INC_SPEED_H_ */
