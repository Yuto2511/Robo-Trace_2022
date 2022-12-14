/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Side_R_Pin GPIO_PIN_2
#define Side_R_GPIO_Port GPIOA
#define Side_L_Pin GPIO_PIN_3
#define Side_L_GPIO_Port GPIOA
#define gyro_switch_Pin GPIO_PIN_4
#define gyro_switch_GPIO_Port GPIOC
#define gyro_switchC5_Pin GPIO_PIN_5
#define gyro_switchC5_GPIO_Port GPIOC
#define gyro_switchB0_Pin GPIO_PIN_0
#define gyro_switchB0_GPIO_Port GPIOB
#define fullcolor_led_2_Pin GPIO_PIN_1
#define fullcolor_led_2_GPIO_Port GPIOB
#define fullcolor_led_2B2_Pin GPIO_PIN_2
#define fullcolor_led_2B2_GPIO_Port GPIOB
#define fullcolor_led_1_Pin GPIO_PIN_12
#define fullcolor_led_1_GPIO_Port GPIOB
#define fullcolor_led_1B13_Pin GPIO_PIN_13
#define fullcolor_led_1B13_GPIO_Port GPIOB
#define fullcolor_led_1B14_Pin GPIO_PIN_14
#define fullcolor_led_1B14_GPIO_Port GPIOB
#define motor_L_Pin GPIO_PIN_15
#define motor_L_GPIO_Port GPIOB
#define motor_R_Pin GPIO_PIN_9
#define motor_R_GPIO_Port GPIOA
#define gyro_switchA11_Pin GPIO_PIN_11
#define gyro_switchA11_GPIO_Port GPIOA
#define gyro_switchA12_Pin GPIO_PIN_12
#define gyro_switchA12_GPIO_Port GPIOA
#define ICN_CS_Pin GPIO_PIN_10
#define ICN_CS_GPIO_Port GPIOC
#define fullcolor_led_2B7_Pin GPIO_PIN_7
#define fullcolor_led_2B7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
