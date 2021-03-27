#include "dimmer.h"
#include "gpio.h"
#include "tim.h"
/******************************************************************************
**		1. Dimmer_Interrupt() must be placed in TIMx_IRQHandler().
**		2. TIMx must enter interrupt 1 time in 40mks.
**		3. 0 =< (*pDimmer).Duty_Cycle =< 255, where 0 - maximum, 255 minimum.
******************************************************************************/
void Dimmer_Interrupt(struct sDimmer *pDimmer) {
  (*pDimmer).Tick++;
  if ((*pDimmer).Tick > (*pDimmer).Duty_Cycle)
	HAL_GPIO_WritePin((*pDimmer).GPIOx, (*pDimmer).GPIO_Pin, GPIO_PIN_SET);
}

/******************************************************************************
**		1. Dimmer_Detect_Rising() and Dimmer_Detect_Falling must be placed in
**	HAL_GPIO_EXTI_Callback().
**		2. Source of EXTI must be pin connected to zero crossing detector.
**		3. Must be switching condition between Dimmer_Detect_Rising() and
**	Dimmer_Detect_Falling(). Use (*pDimmer).R_or_F to switch between them.
******************************************************************************/
void Dimmer_Detect_Rising(struct sDimmer *pDimmer) {
  (*pDimmer).Tick = 0;
  (*pDimmer).R_or_F = 1;
  HAL_TIM_Base_Start_IT((*pDimmer).htim);
  CLEAR_BIT(EXTI->FTSR, EXTI_FTSR_TR2);		//Falling trigger disabled
  SET_BIT(EXTI->RTSR, EXTI_FTSR_TR2);		//Rising trigger enabled
}

void Dimmer_Detect_Falling(struct sDimmer *pDimmer) {
  (*pDimmer).Tick = 0;
  (*pDimmer).R_or_F = 0;
  HAL_TIM_Base_Stop_IT((*pDimmer).htim);
  HAL_GPIO_WritePin((*pDimmer).GPIOx, (*pDimmer).GPIO_Pin, GPIO_PIN_RESET);
  CLEAR_BIT(EXTI->RTSR, EXTI_FTSR_TR2);		//Rising trigger disabled
  SET_BIT(EXTI->FTSR, EXTI_FTSR_TR2);		//Falling trigger enabled
}

