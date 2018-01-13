#ifndef PatternRhythm_h
#define PatternRhythm_h

#include "Arduino.h"
#include "Rhythm.h"


class PatternRhythm: public Rhythm {

public:
		
	uint16_t patternLength;
	uint8_t *patternValues;

	virtual String title();
	virtual void resetState();
	virtual void check(unsigned long now);

	virtual ~PatternRhythm();

};


#endif