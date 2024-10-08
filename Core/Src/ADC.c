/*
 * ADC.c
 *
 *  Created on: May 7, 2024
 *      Author: rjned
 */

// includes
#include "main.h"


float read_ADC(void){

	uint8_t ADC_rx_buff[4];

	// read data from ADC
	HAL_GPIO_WritePin(GPIOA, CH_ADC_Pin, GPIO_PIN_RESET);
	HAL_SPI_Receive(&hspi1, ADC_rx_buff, 4, 100);
	HAL_GPIO_WritePin(GPIOA, CH_ADC_Pin, GPIO_PIN_SET);

	uint16_t result = (ADC_rx_buff[2] << 8) + (ADC_rx_buff[3]);
	result = (result >> 2);

	return (3.3 * (float)result / 16384);
}

