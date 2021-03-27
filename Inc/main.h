/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

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
#define DIM1_ZERO_Pin GPIO_PIN_2
#define DIM1_ZERO_GPIO_Port GPIOA
#define DIM1_ZERO_EXTI_IRQn EXTI2_TSC_IRQn
#define DIM2_ZERO_Pin GPIO_PIN_3
#define DIM2_ZERO_GPIO_Port GPIOA
#define DIM2_ZERO_EXTI_IRQn EXTI3_IRQn
#define MAX31855_CS_1_Pin GPIO_PIN_0
#define MAX31855_CS_1_GPIO_Port GPIOB
#define MAX31855_CS_2_Pin GPIO_PIN_1
#define MAX31855_CS_2_GPIO_Port GPIOB
#define MAX31855_CS_3_Pin GPIO_PIN_2
#define MAX31855_CS_3_GPIO_Port GPIOB
#define NEXTION_RX_MCU_TX_Pin GPIO_PIN_9
#define NEXTION_RX_MCU_TX_GPIO_Port GPIOA
#define NEXTION_TX_MCU_RX_Pin GPIO_PIN_10
#define NEXTION_TX_MCU_RX_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
