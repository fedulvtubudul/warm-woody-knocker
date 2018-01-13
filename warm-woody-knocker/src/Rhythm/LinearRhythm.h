#ifndef LinearRhythm_h
#define LinearRhythm_h

#include "Arduino.h"
#include "Rhythm.h"


class LinearRhythm: public Rhythm {

public:
	
	uint16_t tempo;
	unsigned long beatDuration;
	unsigned long measureStart;


	uint16_t patternLength;
	uint8_t *patternValues;

	virtual String title();
	virtual void resetState();
	virtual void check(unsigned long now);

	virtual ~LinearRhythm();

};


#endif
