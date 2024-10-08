/*
 * USB_voltammogram.h
 *
 *  Created on: Oct 5, 2024
 *      Author: rjned
 */

#ifndef INC_USB_VOLTAMMOGRAM_H_
#define INC_USB_VOLTAMMOGRAM_H_

extern uint8_t USB_buffer[3000];
extern float buf_float[300];

float USB_get_num(void);
void USB_get_voltammogram(void);

#endif /* INC_USB_VOLTAMMOGRAM_H_ */
