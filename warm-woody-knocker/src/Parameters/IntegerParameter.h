#ifndef IntegerParameter_h
#define IntegerParameter_h

#include "Arduino.h"
#include "Parameter.h"
#include "../Storage/StoredParameter.h"


class Storage;


class IntegerParameter : public Parameter {

public:

	IntegerParameter(String *title, Storage *storage, StoredParameter parameter, int minValue, int maxValue, int initialValue, void (*onChange)(IntegerParameter *sender) = nullptr);
	~IntegerParameter();
	
	int getValue();
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
