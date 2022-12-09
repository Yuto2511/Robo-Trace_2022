/*
 * LineTrace.h
 *
 *  Created on: Oct 27, 2022
 *      Author: efmgh
 */

#ifndef INC_LINETRACE_H_
#define INC_LINETRACE_H_

#include "speed.h"
#include "motor.h"
#include "AnalogSensor.h"
#include "macro.h"
#include "Speed_Contorol.h"
#include "flash_memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Trace_Init();
void TraceDebug();
void LineTrace(uint8_t motor_falg, uint8_t memory_flag);

double Speed_input_R, Speed_input_L, Turning_Radius, tread, theta, degree;
uint8_t Start_Flag;
int Time;

#endif /* INC_LINETRACE_H_ */
