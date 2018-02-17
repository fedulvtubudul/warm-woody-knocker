#ifndef EnumParameter_h
#define EnumParameter_h

#include "Arduino.h"
#include "Parameter.h"


class EnumParameter : public Parameter {

public:

	EnumParameter(String *title, void (*onChange)(EnumParameter *sender), int valuesCount, String *valueTitles);
	~EnumParameter();
	
	virtual void stepBy(int stepValue);
	virtual int getRawValue();
	virtual String printableValue();

private:

	EnumParameter();
	int valuesCount;
	String *valueTitles;
	int currentValue;

};

#endif
