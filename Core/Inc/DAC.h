/*
 * DAC.h
 *
 *  Created on: May 8, 2024
 *      Author: rjned
 */

#ifndef INC_DAC_H_
#define INC_DAC_H_

#define CH0		0x00
#define CH1		0x01

#define SYNC  	0x02
#define CONFIG  0x03
#define TRIGGER 0x05

// extern variables
extern SPI_HandleTypeDef hspi1;
extern uint8_t SPI_tx_flag;

// function
void write_DAC(uint8_t reg, uint16_t data);
void DAC_set(uint8_t channel, float voltage);

#endif /* INC_DAC_H_ */
