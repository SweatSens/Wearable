
#include "main.h"
#include "usbd_cdc_if.h"
#include "string.h"

void execute_SWV(struct settings_swv set){
	// variables SWV
	float E = 0.0, vin = 0.0, lowmeas = 0.0, highmeas = 0.0;
	uint8_t equilibration = 0;
	uint32_t tick;
	uint32_t wait;
	uint32_t start_tick = HAL_GetTick();
	uint8_t print_buf[10];
	uint8_t len_print_buf;

	// begin
	if(set.E_begin < 0.0){
		E = set.E_begin*-1.0;
		vin = set.E_begin*-2.0;
	}
	else{
		E = set.E_begin;
		vin = 0.0;
	}
	DAC_set(CH1, E);
	DAC_set(CH0, vin);
	float period = 1/(2*set.Frequency)*1000;
	float end_SWV = (set.E_end-set.E_begin)/set.E_step;
	uint32_t end_loop_SWV = (uint32_t)end_SWV;
	//start SWV
	for(uint32_t i=0;i<(end_loop_SWV+1);i++){
		if(equilibration == 0){
			HAL_Delay(set.t_equilibration*1000);
			equilibration = 1;
			E = E - set.Amplitude;	// to start
		}
		E = E + set.E_step + 2*set.Amplitude;
		DAC_set(CH1, E);
		HAL_Delay(period-1);
		tick = HAL_GetTick();
		wait = tick + 1;
		highmeas = read_ADC();
		while(wait >= tick){
			HAL_Delay(1);
			tick = HAL_GetTick();
		}
		memset(print_buf,'0',10);
		len_print_buf = float_to_ASCII(highmeas,print_buf);
		print_buf[len_print_buf+1] = 13;
		print_buf[len_print_buf+2] = 10;
		CDC_Transmit_FS(print_buf, len_print_buf+2);
		E = E - 2*set.Amplitude;
		DAC_set(CH1, E);
		HAL_Delay(period-1);
		tick = HAL_GetTick();
		wait = tick + 1;
		lowmeas = read_ADC();
		while(wait >= tick){
			HAL_Delay(1);
			tick = HAL_GetTick();
		}
		memset(print_buf,'0',10);
		len_print_buf = float_to_ASCII(lowmeas,print_buf);
		print_buf[len_print_buf+1] = 13;
		print_buf[len_print_buf+2] = 10;
		CDC_Transmit_FS(print_buf, len_print_buf+2);
	}
	E = 0;
	DAC_set(CH1, E);
	DAC_set(CH0, 0.0);
	equilibration = 0;

	return;
}
