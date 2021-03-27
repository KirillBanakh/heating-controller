#ifndef TIMERS_H
#define TIMERS_H
#include <stdint.h>
#include <stdbool.h>

struct sTimer {
	uint32_t Time;
	uint32_t Counter;	
	bool Auto_Restart;
	bool TimerInUse;
};
int Timer_Start(struct sTimer *pTimer, uint32_t Time, bool Auto_Restart);
int Timer_Stop(struct sTimer *pTimer);
int Timer_Restart(struct sTimer *pTimer, uint32_t Time, bool Auto_Restart);
int Timer_Check(struct sTimer *pTimer);
void Timer_Interrupt(struct sTimer *pTimer);

#endif