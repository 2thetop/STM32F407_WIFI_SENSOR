/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_WHITE_Pin GPIO_PIN_4
#define LED1_WHITE_GPIO_Port GPIOA
#define LED2_RED_Pin GPIO_PIN_5
#define LED2_RED_GPIO_Port GPIOA
#define LED3_BLUE_Pin GPIO_PIN_6
#define LED3_BLUE_GPIO_Port GPIOA
#define LED4_YELLOW_Pin GPIO_PIN_7
#define LED4_YELLOW_GPIO_Port GPIOA
#define ESP_nRESET_Pin GPIO_PIN_4
#define ESP_nRESET_GPIO_Port GPIOC
#define ESP_GPIO_0_Pin GPIO_PIN_5
#define ESP_GPIO_0_GPIO_Port GPIOC
#define FLASH_CS_Pin GPIO_PIN_0
#define FLASH_CS_GPIO_Port GPIOB
#define TACT_SW1_Pin GPIO_PIN_10
#define TACT_SW1_GPIO_Port GPIOD
#define TACT_SW2_Pin GPIO_PIN_11
#define TACT_SW2_GPIO_Port GPIOD
#define DIP_SW1_Pin GPIO_PIN_12
#define DIP_SW1_GPIO_Port GPIOD
#define DIP_SW2_Pin GPIO_PIN_13
#define DIP_SW2_GPIO_Port GPIOD
#define DIP_SW3_Pin GPIO_PIN_14
#define DIP_SW3_GPIO_Port GPIOD
#define DIP_SW4_Pin GPIO_PIN_15
#define DIP_SW4_GPIO_Port GPIOD
#define LED5_GREEN_Pin GPIO_PIN_8
#define LED5_GREEN_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
