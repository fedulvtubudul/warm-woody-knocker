#ifndef EnumParameter_h
#define EnumParameter_h

#include "Arduino.h"
#include "Parameter.h"


class EnumParameter : public Parameter {

public:

	EnumParameter(String *title, int valuesCount, String *valueTitles);
	~EnumParameter();
	
	virtual void stepBy(int stepValue);
	virtual String printableValue();

private:

	EnumParameter();
	int valuesCount;
	String *valueTitles;
	int currentValue;

};

#endif
