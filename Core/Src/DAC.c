/*
 * DAC.c
 *
 *  Created on: May 8, 2024
 *      Author: rjned
 */

// includes
#include "main.h"

void write_DAC(uint8_t reg, uint16_t data){
	uint8_t DAC_tx_buff[3] = {(0x0F&reg), (uint16_t)(data>>8), (uint16_t)(data&0x00FF)};

	// write data to DAC1
	HAL_GPIO_WritePin(GPIOA, CS_DAC_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, DAC_tx_buff, 3,100);
	HAL_GPIO_WritePin(GPIOA, CS_DAC_Pin, GPIO_PIN_SET);

	return;
}

void DAC_set(uint8_t channel, float voltage){

	uint16_t result = (uint16_t)(voltage/33.0*655360.0);
	uint8_t reg = channel + 8;

	write_DAC(reg, result);

	return;
}
