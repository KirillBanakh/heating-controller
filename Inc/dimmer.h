#ifndef DIMMER_H
#define DIMMER_H

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "timers.h"

struct sDimmer {
	GPIO_TypeDef* GPIOx;	//From HAL library. Port definition (GPIOA, ... , GPIOF)
	uint16_t GPIO_Pin;		//From HAL library. Pin definition (GPIO_PIN_0, ... , GPIO_PIN_15)
	TIM_HandleTypeDef *htim;//From HAL library. Timer definition (htim1, ... , htimx)
	uint32_t Duty_Cycle;	//Duty_Cycle of generated signal
	uint32_t Tick;			//Tick to count cycles
	bool R_or_F; 			//1 - Rising. 0 - Falling
};

void Dimmer_Interrupt(struct sDimmer *pDimmer);
void Dimmer_Detect_Rising(struct sDimmer *pDimmer);
void Dimmer_Detect_Falling(struct sDimmer *pDimmer);


#endif