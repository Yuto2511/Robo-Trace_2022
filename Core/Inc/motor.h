/*
 * motor.h
 *
 *  Created on: Oct 27, 2022
 *      Author: efmgh
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim4;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

double SR, SL;

void MotorStart();

void motor_R( double );
void motor_L( double );
void motor_S( double );

double Speed_R();
double Speed_L();

#endif /* INC_MOTOR_H_ */
