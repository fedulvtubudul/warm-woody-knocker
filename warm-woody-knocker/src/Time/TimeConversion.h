#ifndef TimeConversion_h
#define TimeConversion_h

#include "Arduino.h"


unsigned long beatDurationFromBPM(int bpmTempo);
int bpmTempoFromBeatDuration(unsigned long beatDuration);


#endif