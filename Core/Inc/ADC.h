/*
 * ADC.h
 *
 *  Created on: May 7, 2024
 *      Author: rjned
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#define NOP					0x00
#define	READ  				0x10
#define	WRITE  				0x08
#define	SETBIT  			0x18
#define	CLEARBIT  			0x20

#define	SYSTEM_STATUS		0x00
#define	DATA_CFG			0x02
#define	CHANNEL_SEL			0x11


// extern variables
extern SPI_HandleTypeDef hspi1;

// function
float read_ADC(void);

#endif /* INC_ADC_H_ */
