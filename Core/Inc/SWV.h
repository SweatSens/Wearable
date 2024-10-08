/*
 * SWV.h
 *
 *  Created on: Oct 4, 2024
 *      Author: rjned
 */

#ifndef INC_SWV_H_
#define INC_SWV_H_

struct settings_swv{
	float E_begin;
	float Frequency;
	float E_end;
	float E_step;
	float Amplitude;
	float t_equilibration;
};

// functions
void execute_SWV(struct settings_swv set);

#endif /* INC_SWV_H_ */
