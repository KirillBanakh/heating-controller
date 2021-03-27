#include "timers.h"
#include "stm32f3xx_hal.h"

int Timer_Start(struct sTimer *pTimer, uint32_t Time, bool Auto_Restart){
  if ((*pTimer).TimerInUse == 1)
	return -1;
  else {
	(*pTimer).Time = Time;
	(*pTimer).Counter = Time;
	(*pTimer).Auto_Restart = Auto_Restart;
	(*pTimer).TimerInUse = 1;
	return 1;
  }
}

int Timer_Stop(struct sTimer *pTimer){
  if ((*pTimer).TimerInUse != 1)
	return -1;
  else {
	(*pTimer).Time = 0;
	(*pTimer).Counter = 0;
	(*pTimer).TimerInUse = 0;
	return 1;
  }
}

int Timer_Restart(struct sTimer *pTimer, uint32_t Time, bool Auto_Restart){
  if ((*pTimer).TimerInUse != 1)
	return -1;
  else {
	Timer_Stop(pTimer);
	Timer_Start(pTimer, Time, Auto_Restart);
	return 1;
  }
}

int Timer_Check(struct sTimer *pTimer) {
  if ((*pTimer).TimerInUse != 1)
	return -1;
  else
	return (*pTimer).Counter;
}

void Timer_Interrupt(struct sTimer *pTimer){
  if ((*pTimer).TimerInUse != 1)
	return;
  else
	if((*pTimer).Counter != 0)
	  (*pTimer).Counter--;
	else
	  if ((*pTimer).Auto_Restart == 1)
		Timer_Restart(pTimer, (*pTimer).Time, 1);
	  else
		Timer_Stop(pTimer);
}