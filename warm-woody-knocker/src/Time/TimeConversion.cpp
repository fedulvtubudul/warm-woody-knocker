#include "TimeConversion.h"


#define BPM_TO_MICRO 60000000lu


unsigned long beatDurationFromBPM(int bpmTempo) {
	return BPM_TO_MICRO / bpmTempo;
}