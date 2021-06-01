#ifndef EnumParameter_h
#define EnumParameter_h

#include "Arduino.h"
#include "Parameter.h"
#include "../Storage/StoredParameter.h"


class Storage;


class EnumParameter : public Parameter {

public:

	EnumParameter(String *title, Storage *storage, StoredParameter parameter, int valuesCount, String *valueTitles, void (*onChange)(EnumParameter *sender) = nullptr);
	~EnumParameter();
	
	virtual void scroll(int stepValue);
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
