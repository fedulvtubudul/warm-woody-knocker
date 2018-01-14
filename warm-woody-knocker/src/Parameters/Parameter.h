#ifndef Parameter_h
#define Parameter_h

#include "Arduino.h"


class Parameter {

public:

	virtual ~Parameter();
	Parameter(String *title, void (*onChange)(void));

	String *getTitle();
	virtual void stepBy(int stepValue) = 0;
	virtual String printableValue() = 0;

protected:

	void notify();

private :
	
	String *title;
	void (*onChange)(void);

	Parameter();

};

#endif
