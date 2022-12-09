/*
 * AnalogSensor.h
 *
 *  Created on: Oct 28, 2022
 *      Author: efmgh
 */

#ifndef INC_ANALOGSENSOR_H_
#define INC_ANALOGSENSOR_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "macro.h"

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

void ADCStart();
void adc_getValues();
void updateValues();
void Sens_Calibration();

uint32_t num;
uint16_t line_R1_[10], line_R2_[10], line_L1_[10], line_L2_[10], stear_[10];
uint16_t analog_[ADC_SENS];
int R_Min, R_Max, L_Min, L_Max;
float Line_Sens_R, Line_Sens_L, Stear_Sens, Line_Calib_R, Line_Calib_L;

#endif /* INC_ANALOGSENSOR_H_ */
