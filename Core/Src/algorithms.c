/*
 * algorithms.c
 *
 *  Created on: Sep 22, 2024
 *      Author: rjned
 */

#include "main.h"

// remove baseline
void baseline_correction(struct voltammogram *val, uint16_t threshold){
	uint16_t l = val->length;
	// remove oxidation peak
	uint16_t x = 0;
	uint16_t replacement = 1;
	float avg;

	float baseline[l];
	for(uint16_t k=0;k<l;k++){
		baseline[k] = val->I[k];
	}

	while((x < threshold) && (replacement > 0)){
		uint16_t replacement = 0;
		for(uint16_t i=1;i<l-1;i++){
			avg = (baseline[i-1]+baseline[i+1])/2;
			if(baseline[i] > avg){
				baseline[i] = avg;
				replacement = replacement + 1;
			}
		}
		x = x + 1;
	}
	// baseline correction
	for(uint16_t j=0;j<l;j++){
		val->I[j] = val->I[j]- baseline[j];
		if(val->I[j] > 3000){
			val->I[j] = 0;
		}
	}

	return;
}

// window the data
void window(struct voltammogram *val, float low, float high){
    uint16_t l = val->length;

    for(uint16_t i=0;i<l;i++){
        if((val->U[i] < low) || (val->U[i] > high)){
        	val->I[i] = 0;
		}
	}
	return;
}

// get the peak of the current
void get_peak(struct voltammogram *val){

	val->peakI = 0;
	for(uint16_t i=0;i<val->length;i++){
		if(val->I[i] > val->peakI){
			 val->peakI = val->I[i];
			 val->peakU = val->U[i];
		}
	}

	return;
}

// fit gaussian
struct voltammogram gaussian_fit(struct voltammogram val){
	struct voltammogram result = {
			.length = val.length,
			.peakI = val.peakI,
			.peakU = val.peakU,
	};
	float a = val.peakI - 0.001;
	float b = val.peakU;
	float c = 0.01;
	float f[20];
	uint16_t index = 0;

	// find U peak
	uint16_t peakUi = 0;
	for(uint16_t i=0;i<val.length;i++){
		if(val.U[i]>b){
			peakUi = i;
			break;
		}
	}

	// compute gaussian fit (of the peak only)
	for(uint16_t i=peakUi-10;i<peakUi+10;i++){
		f[index] = a*exp(-pow(((val.U[i]-b)/c),2));
		index++;
	}

	// fit gaussian
	uint16_t threshold = 1;
	uint8_t bound = 0;
	while((bound != 1) && (threshold != 1000)){
	    c = c + 0.001;	// increase c

	    // compute gaussian fit (of the peak only)
		float f[20];
		index = 0;
		for(uint16_t i=peakUi-10;i<peakUi+10;i++){
			f[index] = a*exp(-pow(((val.U[i]-b)/c),2));
			index++;
		}

		// check the peak
		index = 0;
		for(uint16_t i=peakUi-10;i<peakUi+10;i++){
			if(val.I[i] < f[index]){
				bound = 1;
			}
			index++;
		}

	    threshold = threshold + 1;
	}

	// calculate the whole gaussian to return
	index = 0;
	for(uint16_t i=1;i<val.length;i++){
		result.I[index] = a*exp(-pow(((val.U[i]-b)/c),2));
		result.U[index] = val.U[index];
		if(result.I[index] < 0.0001){
			result.I[index] = 0.0;
		}
		index++;
	}


	return result;
}

struct voltammogram subGaus(struct voltammogram gaus, struct voltammogram val){
	struct voltammogram result;

	for(uint16_t i=1;i<val.length;i++){
		result.I[i] = val.I[i] - gaus.I[i];
		result.U[i] = val.U[i];
		if(result.I[i] > 3000){
			result.I[i] = 0;
		}
	}

	return result;
}


