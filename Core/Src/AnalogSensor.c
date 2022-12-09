/*
 * AnalogSensor.c
 *
 *  Created on: Oct 28, 2022
 *      Author: efmgh
 */

#include "AnalogSensor.h"

void ADCStart()
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *) analog_, 5);
	R_Min = L_Min = 1000;
	R_Max = L_Max = 0;
}

void adc_getValues()
{
	if (num >= 9) num = 0;
	line_R1_[num] = analog_[4];
	line_R2_[num] = analog_[3];
	line_L1_[num] = analog_[2];
	line_L2_[num] = analog_[1];
	stear_[num] = analog_[0];
	num++;
}

void updateValues()
{
	uint32_t tmp;
	for(int i = 0; i < 10; i++){
		for(int j = i+1; j < 10; j++){
			if(line_R1_[i] > line_R1_[j]){
				tmp = line_R1_[i];
				line_R1_[i] = line_R1_[j];
				line_R1_[j] = tmp;
			}
			if(line_R2_[i] > line_R2_[j]){
				tmp = line_R2_[i];
				line_R2_[i] = line_R2_[j];
				line_R2_[j] = tmp;
			}
			if(line_L1_[i] > line_L1_[j]){
				tmp = line_L1_[i];
				line_L1_[i] = line_L1_[j];
				line_L1_[j] = tmp;
			}
			if(line_L2_[i] > line_L2_[j]){
				tmp = line_L2_[i];
				line_L2_[i] = line_L2_[j];
				line_L2_[j] = tmp;
			}
			if(stear_[i] > stear_[j]){
				tmp = stear_[i];
				stear_[i] = stear_[j];
				stear_[j] = tmp;
			}
		}
	}
	Line_Sens_R = (line_R1_[4] + line_R2_[5]) / 2;
	Line_Sens_L = (line_L1_[4] + line_L2_[5]) / 2;
	Stear_Sens = (stear_[4] + stear_[5]) / 2;

	Line_Calib_R = ((Line_Sens_R - (double)R_Min) / (double)(R_Max - R_Min)) * 1000;
	Line_Calib_L = ((Line_Sens_L - (double)L_Min) / (double)(L_Max - L_Min)) * 1000;
}

void Sens_Calibration()
{
	if(Line_Sens_R <= R_Min) R_Min = Line_Sens_R;
	if(Line_Sens_R >= R_Max) R_Max = Line_Sens_R;
	if(Line_Sens_L <= L_Min) L_Min = Line_Sens_L;
	if(Line_Sens_L >= L_Max) L_Max = Line_Sens_L;
}
