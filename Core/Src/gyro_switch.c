/*
 * gyro_switch.c
 *
 *  Created on: Oct 27, 2022
 *      Author: efmgh
 */

#include "gyro_switch.h"

uint16_t switch_get()
{
	uint16_t value = 0;

	if(!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4)) value |= 0x10;
	else if(!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)) value |= 0x08;
	else if(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)) value |= 0x01;
	else if(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)) value |= 0x04;
	else if(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)) value |= 0x02;
	else value |= 0x00;

	return value;
}


