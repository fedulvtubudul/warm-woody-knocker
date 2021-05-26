#ifndef StoredParameter_h
#define StoredParameter_h

#include "Arduino.h"



// EEPROM memory layout:
// 0x0000: Scheme version (uint16_t)
// 0x0002: Rhythm (uint8_t)
// 0x0003: Volume (uint16_t)
// 0x0005: Tempo (uint16_t)
// 0x0007: Meter (uint8_t)
// 0x0008: Division (uint8_t)
// 0x0009: Pattern (uint16_t)

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
