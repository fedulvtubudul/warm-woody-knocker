#ifndef LinearRhythm_h
#define LinearRhythm_h

#include "Arduino.h"
#include "Rhythm.h"


class LinearRhythm: public Rhythm {

public:
	
	virtual String title();

	uint16_t patternLength;
	uint8_t *patternValues;

	virtual ~LinearRhythm();

};


#endif
