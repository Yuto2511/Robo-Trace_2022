/*
 * flash_memory.c
 *
 *  Created on: Nov 24, 2022
 *      Author: efmgh
 */

#include "flash_memory.h"

double Calculate_Mileage(int flag)
{
	double median;
	uint32_t cros_buff;
	Milage += ((-SR + SL) / 2) * (TIM05 / 10);
	Gyro = (z_gyro() /16.4) * M_PI / 180;
	Score_Time += TIM05;

	switch(flag){
		case 0:
			Milage = data_num = Score_Time = crossing_buff = 0;
			Cal_Speed = MIN_SPEED;
			return 0;
			break;
		case 1:
			if(Milage / 5 >= data_num){
				write_data_sector11.Omega[data_num] = Gyro * 1000;
				write_data_sector11.speed_R[data_num] = -SR * 1000;
				write_data_sector11.speed_L[data_num] = SL * 1000;
				write_data_sector10.time[data_num] = Score_Time;
				write_data_sector10.milage[data_num] = Milage;	//cm
				data_num++;
			}

			if(Crossing_Flag != crossing_buff) write_data_sector10.marker_milage[Crossing_Flag] = Milage;
			crossing_buff = Crossing_Flag;

			return MIN_SPEED;
			break;
		case 2:
			if(Milage >= (double)(Section[data_num][0] / 10)) data_num++;
			/*
			if(Crossing_Flag != crossing_buff && Milage > read_data_sector10.marker_milage[Crossing_Flag]+15){
				Crossing_Flag++;
				Milage = read_data_sector10.marker_milage[Crossing_Flag];
			}
			else if(Crossing_Flag != crossing_buff && Milage < read_data_sector10.marker_milage[Crossing_Flag]-15){
				Crossing_Flag--;
				Milage = read_data_sector10.marker_milage[Crossing_Flag];
			}
			else if (Crossing_Flag != crossing_buff) Milage = read_data_sector10.marker_milage[Crossing_Flag];
			crossing_buff = Crossing_Flag;
			*/
			if(Crossing_Flag == 1){
				if( labs(Milage - read_data_sector10.marker_milage[1]) <= 10 ) Milage = read_data_sector10.marker_milage[1];
			}

			//straight
			if(Section[data_num][1]){
				median = (((double)Section[data_num][0] - (double)Section[data_num-1][0]) / 2) + (double)Section[data_num-1][0];
				if(Milage <= median/10 ){
					Cal_Speed += (ACC * TIM05 / 1000);
					if(Cal_Speed >= MAX_SPEED*coe) Cal_Speed = MAX_SPEED*coe;
				}
				else if(Milage > median/10 ){
					Cal_Speed -= (ACC * TIM05 / 1000);
					if(Cal_Speed <= MIN_SPEED) Cal_Speed = MIN_SPEED;
				}
				return Cal_Speed;
			}
			//curve
			else if(!Section[data_num][1]){
				return MIN_SPEED;
			}
			break;
		default:
			return 0;
			break;

	}
}

void run_section()
{
	double velocity, angular_velocity, curvature_radius;
	double boundary = 0.4;
	int j = 0;

	for(int i= 0; i < CM_COUNT; i++){
		velocity = ((double)read_data_sector11.speed_L[i] + (double)read_data_sector11.speed_R[i]) / 2000;
		//angular_velocity = (double)write_data_sector11.Omega[i] / 100;
		angular_velocity = ((double)read_data_sector11.speed_R[i] - (double)read_data_sector11.speed_L[i]) / (0.1085 * 1000);
		curvature_radius = velocity / angular_velocity;

		if(curvature_radius >= boundary || curvature_radius <= -boundary) Radius_Flag[i] = 1;
		else Radius_Flag[i] = 0;

		//mm
		if(i > 0) Second_Mileage[i][0] = Second_Mileage[i-1][0] + velocity*(((double)read_data_sector10.time[i] - (double)read_data_sector10.time[i-1]) / 1);
		else Second_Mileage[0][0] = velocity * ((double)read_data_sector10.time[0] / 1);
	}

	for(int i = 0; i < CM_COUNT; i++){
		if(Radius_Flag[i] && !Radius_Flag[i+1] && Radius_Flag[i+2]) Second_Mileage[i+1][1] = 1;
		if(!Radius_Flag[i] && Radius_Flag[i+1] && !Radius_Flag[i+2]) Second_Mileage[i+1][1] = 0;
		if(Radius_Flag[i] && !Radius_Flag[i+1] && !Radius_Flag[i+2] && Radius_Flag[i+3]){
			Second_Mileage[i+1][1] = 1;
			Second_Mileage[i+2][1] = 1;
		}
		if(!Radius_Flag[i] && Radius_Flag[i+1] && Radius_Flag[i+2] && !Radius_Flag[i+3]){
			Second_Mileage[i+1][1] = 0;
			Second_Mileage[i+2][1] = 0;
		}
		else Second_Mileage[i][1] = Radius_Flag[i];
	}

	HAL_Delay(100);

	Section[0][0] = 0;
	Section[0][1] = 0;
	j = 1;
	for(int i = 1; i < CM_COUNT; i++){
		if(Second_Mileage[i][1] && !Second_Mileage[i+1][1]){
			Section[j][0] = Second_Mileage[i][0];
			Section[j][1] = Second_Mileage[i][1];
			j++;
		}
		else if(!Second_Mileage[i][1] && Second_Mileage[i+1][1]){
			Section[j][0] = Second_Mileage[i][0];
			Section[j][1] = Second_Mileage[i][1];
			j++;
		}
	}

	for(int i = 1; i < 150; i++){
		if(!Section[i][1]) Section[i][0] += 200;
		else if(Section[i][1]) Section[i][0] -= 120;
	}

	//for(int i = 0; i < CM_COUNT; i++) printf("Mileage -> %d	%d\r\n", Second_Mileage[i][0], Second_Mileage[i][1]);
	//for(int i = 0; i < 150; i++) printf("Mileage -> %d	%d\r\n", Section[i][0], Section[i][1]);

}

void eraseFlash(uint8_t sector)
{
	FLASH_EraseInitTypeDef erase;
	erase.TypeErase = FLASH_TYPEERASE_SECTORS;
	if(sector == 10) erase.Sector = FLASH_SECTOR_10;
	else if(sector == 11) erase.Sector = FLASH_SECTOR_11;
	erase.NbSectors = 1;
	erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;

	uint32_t pageError = 0;

	HAL_FLASHEx_Erase(&erase, &pageError);
}

//Write Data to Flash
void writeFlash(uint32_t address, uint8_t *data, uint32_t size, uint8_t sector)
{
	HAL_FLASH_Unlock();
	eraseFlash(sector);

	for(uint32_t add = address; add < (address + size); add++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, add, *data);
		data++;
	}

	HAL_FLASH_Lock();
}

//load Data from Flash
void loadFlash(uint32_t address, uint8_t *data, uint32_t size)
{
	memcpy(data, (uint8_t*)address, size);
}

