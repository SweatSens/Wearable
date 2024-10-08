/*
 * algorithms.h
 *
 *  Created on: Sep 22, 2024
 *      Author: rjned
 */

#ifndef INC_ALGORITHMS_H_
#define INC_ALGORITHMS_H_

// includes
#include "math.h"

struct voltammogram{
	uint16_t length;
	float I[300];
	float U[300];
	float peakI;	// remove
	float peakU; // remove
};

struct peaks{
	float peakI;
	float peakU;
	struct voltammogram vol;
};

struct MTX{
	float IMTX;
	float UMTX;
};

// functions
void baseline_correction(struct voltammogram *val, uint16_t threshold);
void window(struct voltammogram *val, float low, float high);
void get_peak(struct voltammogram *val);
struct voltammogram gaussian_fit(struct voltammogram val);
struct voltammogram subGaus(struct voltammogram gaus, struct voltammogram val);

#endif /* INC_ALGORITHMS_H_ */
