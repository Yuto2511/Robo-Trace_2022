/*
 * wrapper.h
 *
 *  Created on: Oct 27, 2022
 *      Author: efmgh
 */

#ifndef INC_WRAPPER_H_
#define INC_WRAPPER_H_

#include <stdio.h>

#include "stm32f4xx_hal.h"

#include "macro.h"
#include "fullcolor_led.h"
#include "gyro_switch.h"
#include "ICM_20648.h"
#include "Accelerometer.h"
#include "motor.h"
#include "AnalogSensor.h"
#include "side_sensor.h"
#include "Speed_Contorol.h"
#include "flash_memory.h"

#include "LineTrace.h"

uint8_t LineTrace_Flag;
uint8_t Memory_Flag;

void init();
void main_loop();
void PeriodElapsed_50us();
void PeriodElapsed_500us();

#endif /* INC_WRAPPER_H_ */
