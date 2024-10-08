/*
 * USB_voltammogram.c
 *
 *  Created on: Oct 5, 2024
 *      Author: rjned
 */

// includes
#include "main.h"

float USB_get_num(void){

	  uint32_t i=0;
	  uint8_t while_end = 0;
	  float val = 0.0;
	  while(while_end != 1){
		  if(USB_buffer[i] == 13){
			  val = ASCII_to_float(0,i,USB_buffer);
			  if(USB_buffer[i] == 13){
				  while_end = 1;
			  }
		  }
		  i++;
	  }
	  memset(USB_buffer,'0',3000);
	  USB_buffer[0] = 82;

	  return val;
}

void USB_get_voltammogram(void){

	  if(USB_buffer[0] != 82){
		  uint32_t i=0;
		  uint8_t while_end = 0;
		  uint32_t float_cntr = 0;
		  memset(buf_float,0,300);
		  uint8_t num_flag = 0;
		  uint32_t old_i = 0;
		  while(while_end != 1){
			  if((USB_buffer[i] == 0x2C && num_flag == 1)||(USB_buffer[i] == 13)){
				  buf_float[float_cntr] = ASCII_to_float(old_i,i,USB_buffer);
				  num_flag = 0;
				  float_cntr ++;
				  if(USB_buffer[i] == 13){
					  while_end = 1;
				  }
			  }
			  if(i == 0){
				  old_i = i;
				  num_flag = 1;
			  }
			  if(USB_buffer[i] == 0x2C){
				  old_i = i+1;
				  num_flag = 1;
			  }
			  i++;
		  }
		  memset(USB_buffer,'0',3000);
		  USB_buffer[0] = 82;
	  }

	  return;
}
