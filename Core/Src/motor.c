/*
 * motor.c
 *
 *  Created on: Oct 27, 2022
 *      Author: efmgh
 */

#include "motor.h"
#include "macro.h"

#include <math.h>

void MotorStart()
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);

	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
}

void motor_R( double duty )
{
	int countorperiod = 0;
	if( duty < 0 ){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
		countorperiod = duty * -1;
	}
	else if( duty >= 0 ){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
		countorperiod = duty;
	}

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, countorperiod);
}

void motor_L( double duty )
{
	int countorperiod = 0;
	if( duty < 0 ){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		countorperiod = duty * -1;
	}
	else if( duty >= 0 ){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		countorperiod = duty;
	}

	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, countorperiod);
}

void motor_S( double duty )
{
	int countorperiod = 0;
	if( duty < 0 ){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
		countorperiod = duty * -1;
	}
	else if( duty >= 0 ){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
		countorperiod = duty;
	}

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, countorperiod);
}


// v = r * 2pi * (3/40960) * (dC/dt)
// m/s
double Speed_R()
{
	int Encoder = (TIM2 -> CNT) - 32767;
	TIM2 -> CNT = 32767;
	double speed = (7. * TIRE * M_PI * (double)Encoder) / (40960. * TIM05);
	return speed;
}

double Speed_L()
{
	int Encoder = (TIM3 -> CNT) - 32767;
	TIM3 -> CNT = 32767;
	double speed = (7. * TIRE * M_PI * (double)Encoder) / (40960. * TIM05);
	return speed;
}
