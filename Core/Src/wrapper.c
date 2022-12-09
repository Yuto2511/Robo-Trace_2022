/*
 * wrapper.c
 *
 *  Created on: Oct 27, 2022
 *      Author: efmgh
 */

#include "wrapper.h"

void init()
{
	IMU_init();
	ADCStart();
	MotorStart();
	Trace_Init();
	stop_init();
	coe = 1;
}

void main_loop()
{

	while(1){
		LineTrace_Flag = 0;
		fullcolor_led( 1, 'W' );
		fullcolor_led( 2, 'R' );
		if( switch_get() == GYRO_A ){
			fullcolor_led( 1, 'C' );
			coe = 0.88;
		}
		else if( switch_get() == GYRO_B ){
			fullcolor_led( 1, 'G' );
			writeFlash(start_address_sector11, (uint8_t*)&write_data_sector11, sizeof(WRITE_DATA_SECTOR11), 11);
			writeFlash(start_address_sector10, (uint8_t*)&write_data_sector10, sizeof(WRITE_DATA_SECTOR10), 10);
		}
		else if( switch_get() == GYRO_C ){
			fullcolor_led( 1, 'B' );
			break;
		}
		else if( switch_get() == GYRO_D ){
			fullcolor_led( 1, 'O' );
			loadFlash(start_address_sector11, (uint8_t*)&read_data_sector11, sizeof(READ_DATA_SECTOR11));
			loadFlash(start_address_sector10, (uint8_t*)&read_data_sector10, sizeof(READ_DATA_SECTOR10));
		}
		else if( switch_get() == GYRO_E ){
			fullcolor_led( 1, 'W' );
			for(int i = 0; i < 100; i ++)
				printf("%d\r\n",  read_data_sector10.marker_milage[i]);
				//printf("%d	%d	%d	%d	%d\r\n", read_data_sector11.speed_L[i], read_data_sector11.speed_R[i], read_data_sector11.Omega[i], read_data_sector10.time[i], read_data_sector10.milage[i]);
		}
		TraceDebug();
		HAL_Delay(100);
	}

	HAL_Delay(500);

	while(1){
		LineTrace_Flag = 0;
		fullcolor_led( 1, 'W' );
		fullcolor_led( 2, 'B' );
		if( switch_get() == GYRO_A ){
			fullcolor_led( 1, 'C' );
			Memory_Flag = 0;
		}
		else if( switch_get() == GYRO_B ){
			fullcolor_led( 1, 'G' );
			Memory_Flag = 1;
		}
		else if( switch_get() == GYRO_C ){
			fullcolor_led( 1, 'M' );
			break;
		}
		else if( switch_get() == GYRO_D ){
			fullcolor_led( 1, 'O' );
			Memory_Flag = 2;
		}
		else if( switch_get() == GYRO_E ){
			fullcolor_led( 1, 'W' );
			run_section();
		}
		//TraceDebug();
		HAL_Delay(100);
	}

	HAL_Delay(500);

	//LineTrace
	while(1){
		fullcolor_led( 1, 'W' );
		fullcolor_led( 2, 'M' );
		if( switch_get() == GYRO_A ){
			fullcolor_led( 1, 'C' );
			Sens_Calibration();
		}
		else if( switch_get() == GYRO_B ){
			fullcolor_led( 1, 'G' );
			coe = 1.12;
		}
		else if( switch_get() == GYRO_C ){
			fullcolor_led( 1, 'R' );
			break;
		}
		else if( switch_get() == GYRO_D ){
			fullcolor_led( 1, 'O' );
			coe = 1.2;
		}
		else if( switch_get() == GYRO_E ){
			fullcolor_led( 1, 'M' );
			LineTrace_Flag = 1;
		}
		//TraceDebug();
		if(LineTrace_Flag && Line_Calib_L + Line_Calib_R >= 1900) break;
		if(start_stop() == 1) LineTrace_Flag = 2;
		if(start_stop() == 2) LineTrace_Flag = 3;
		HAL_Delay(0.5);
	}

	HAL_Delay(500);

}

void PeriodElapsed_50us()
{
	adc_getValues();
}


void PeriodElapsed_500us()
{
	updateValues();
	LineTrace( LineTrace_Flag, Memory_Flag);
	SR = Speed_R();
	SL = Speed_L();
}
