/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DAC.h"
#include "ADC.h"
#include "SWV.h"
#include "ASCII.h"
#include "USB_voltammogram.h"
#include "algorithms.h"
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
#define CH_ADC_Pin GPIO_PIN_0
#define CH_ADC_GPIO_Port GPIOA
#define PDEN_Pin GPIO_PIN_1
#define PDEN_GPIO_Port GPIOA
#define CS_DAC_Pin GPIO_PIN_4
#define CS_DAC_GPIO_Port GPIOA
#define CH_SEL_Pin GPIO_PIN_0
#define CH_SEL_GPIO_Port GPIOB
#define MUX_SEL2_Pin GPIO_PIN_1
#define MUX_SEL2_GPIO_Port GPIOB
#define MUX_SEL1_Pin GPIO_PIN_8
#define MUX_SEL1_GPIO_Port GPIOA
#define RSTSEL_Pin GPIO_PIN_9
#define RSTSEL_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_10
#define LED_GPIO_Port GPIOA
#define EN_4_2VDC_Pin GPIO_PIN_15
#define EN_4_2VDC_GPIO_Port GPIOA
#define EN_REF_Pin GPIO_PIN_4
#define EN_REF_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
