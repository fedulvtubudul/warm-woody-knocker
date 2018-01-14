#ifndef Rhythm_h
#define Rhythm_h

#include "Arduino.h"


class Parameter;


class Rhythm {
	
public:

	virtual String title() = 0;
	virtual void resetState() = 0;
	virtual void check(unsigned long now);
	
	int getParametersCount();
	Parameter *getParameter(int parameterIndex);

	// Rhythm();
	virtual ~Rhythm();

protected:

	int parametersCount;
	Parameter **parameters;

};


#endif
