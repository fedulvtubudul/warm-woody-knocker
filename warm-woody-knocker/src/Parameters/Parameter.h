#ifndef Parameter_h
#define Parameter_h

#include "Arduino.h"


class Parameter {

public:

	String *getTitle();
	virtual void stepBy(int stepValue) = 0;
	virtual String printableValue() = 0;

protected:

	Parameter(String *title);

private :
	
	String *title;

	Parameter();

};

#endif
