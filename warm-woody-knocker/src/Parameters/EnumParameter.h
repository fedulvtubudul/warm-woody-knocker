#ifndef EnumParameter_h
#define EnumParameter_h

#include "Arduino.h"
#include "Parameter.h"


class EnumParameter : public Parameter {

public:

	EnumParameter(String *title, void (*onChange)(EnumParameter *sender), int valuesCount, String *valueTitles, int initialValue);
	~EnumParameter();
	
	virtual void stepBy(int stepValue);
	virtual int getRawValue();
	virtual String printableValue();

protected:

	int valuesCount;
	String *valueTitles;
	int value;

private:

	EnumParameter();

};

#endif
