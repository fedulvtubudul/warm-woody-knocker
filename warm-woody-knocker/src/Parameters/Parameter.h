#ifndef Parameter_h
#define Parameter_h

#include "Arduino.h"


class Parameter {

public:

	virtual ~Parameter();
	Parameter(String *title, void (*onChange)(Parameter *sender));

	String *getTitle();
	virtual void stepBy(int stepValue) = 0;
	virtual String printableValue() = 0;

protected:

	virtual void notify();

private :
	
	String *title;
	void (*onChange)(Parameter *sender);

	Parameter();

};

#endif
