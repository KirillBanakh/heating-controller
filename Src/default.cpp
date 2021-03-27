#include "default.h"
#include "timers.h"

using namespace TIMERS;
sTimers sDefault_Timer[1];
cTimers cDefault_Timer (sDefault_Timer, 1);

void Default() {
  cDefault_Timer.Start(1000, 1);
}