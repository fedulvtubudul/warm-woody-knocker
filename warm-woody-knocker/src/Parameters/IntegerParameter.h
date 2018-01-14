#ifndef IntegerParameter_h
#define IntegerParameter_h

#include "Arduino.h"
#include "Parameter.h"


class IntegerParameter : public Parameter {

public:

	IntegerParameter(String *title, void (*onChange)(void), int minValue, int maxValue, int initialValue);
	~IntegerParameter();
	
	virtual void stepBy(int stepValue);
	virtual String printableValue();

protected:

	int minValue;
	int maxValue;
	int value;

private:

	IntegerParameter();

};

#endif
