#ifndef Rhythm_h
#define Rhythm_h

#include "Arduino.h"


class RhythmParameter;


class Rhythm {
	
public:

	virtual String title() = 0;
	virtual void resetState() = 0;
	virtual void check(unsigned long now);
	
	int getParametersCount();
	// virtual RhythmParameter *parameters() = 0;

	// Rhythm();
	virtual ~Rhythm();

protected:

	int parametersCount;

};


#endif
