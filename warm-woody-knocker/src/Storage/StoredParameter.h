#ifndef StoredParameter_h
#define StoredParameter_h

#include "Arduino.h"


enum StoredParameter : int {
    storedParameterScheme,
    storedParameterRhythm,
    storedParameterVolume,
    storedParameterTempo,
    storedParameterMeter,
    storedParameterDivision,
    storedParameterPattern,

	storedParametersCount
};


#endif
