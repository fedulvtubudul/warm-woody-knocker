#ifndef EnumParameter_h
#define EnumParameter_h

#include "Arduino.h"
#include "Parameter.h"


class EnumParameter : public Parameter {

public:

	EnumParameter(String *title, int valuesCount, String *valueTitles, int initialValue, void (*onChange)(EnumParameter *sender) = nullptr);
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
