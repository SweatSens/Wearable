/*
 * USB_voltammogram.h
 *
 *  Created on: Oct 5, 2024
 *      Author: rjned
 */

#ifndef INC_USB_VOLTAMMOGRAM_H_
#define INC_USB_VOLTAMMOGRAM_H_

#include "string.h"

#define potential	0x00
#define current		0x01

extern uint8_t USB_buffer[3000];
extern float buf_float[300];
extern struct voltammogram v1;

float USB_get_num(void);
uint32_t USB_get_voltammogram(uint8_t UI, uint32_t cntr);

#endif /* INC_USB_VOLTAMMOGRAM_H_ */
