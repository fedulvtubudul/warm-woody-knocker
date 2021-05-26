#ifndef RelativeParameter_h
#define RelativeParameter_h

#include "Arduino.h"
#include "IntegerParameter.h"
#include "../Storage/StoredParameter.h"


class Storage;


class RelativeParameter : public IntegerParameter {

public:

	RelativeParameter(String *title, Storage *storage, StoredParameter parameter, int steps, int initialStep, void (*onChange)(RelativeParameter *sender) = nullptr);
	~RelativeParameter();

	float relativeValue;

protected:

	virtual void notify();
};

#endif
