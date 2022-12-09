/*
 * flash_memory.h
 *
 *  Created on: Nov 24, 2022
 *      Author: efmgh
 */

#ifndef INC_FLASH_MEMORY_H_
#define INC_FLASH_MEMORY_H_

#include"stm32f4xx_hal.h"
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>

#include "macro.h"
#include "motor.h"
#include "Accelerometer.h"
#include "fullcolor_led.h"

double Milage, Score_Time, Gyro, Cal_Speed;
int data_num, crossing_buff;
uint16_t sample[CM_COUNT];
uint16_t Radius_Flag[CM_COUNT];
uint32_t Second_Mileage[CM_COUNT][2];
uint32_t Section[150][2];

double Calculate_Mileage(int flag);
void run_section();

void eraseFlash(uint8_t sector);
//Write Data to Flash
void writeFlash(uint32_t address, uint8_t *data, uint32_t size, uint8_t sector);
//load Data from Flash
void loadFlash(uint32_t address, uint8_t *data, uint32_t size);
void *memcpy(
		void * restrict s1,
		const void * restrict s2,
		size_t n
);

extern const uint32_t start_address_sector10;	//sector10 start address
extern const uint32_t end_address_sector10;	//sector10 end address
extern const uint32_t start_address_sector11;	//sector11 start address
extern const uint32_t end_address_sector11;	//sector11 end address

typedef struct
{
	//uint16_t speed_RL[4800];
	int32_t Omega[CM_COUNT];
	uint32_t speed_R[CM_COUNT];
	uint32_t speed_L[CM_COUNT];
}WRITE_DATA_SECTOR11;

typedef struct
{
	//uint16_t speed_RL[4800];
	int32_t Omega[CM_COUNT];
	uint32_t speed_R[CM_COUNT];
	uint32_t speed_L[CM_COUNT];
}READ_DATA_SECTOR11;

typedef struct
{
	uint32_t time[CM_COUNT];
	uint32_t milage[CM_COUNT];
	uint32_t marker_milage[100];
}WRITE_DATA_SECTOR10;

typedef struct
{
	uint32_t time[CM_COUNT];
	uint32_t milage[CM_COUNT];
	uint32_t marker_milage[100];
}READ_DATA_SECTOR10;

extern WRITE_DATA_SECTOR11 write_data_sector11;
extern READ_DATA_SECTOR11 read_data_sector11;
extern WRITE_DATA_SECTOR10 write_data_sector10;
extern READ_DATA_SECTOR10 read_data_sector10;

#endif /* INC_FLASH_MEMORY_H_ */
