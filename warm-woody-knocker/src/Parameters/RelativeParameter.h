#ifndef RelativeParameter_h
#define RelativeParameter_h

#include "Arduino.h"
#include "IntegerParameter.h"


class RelativeParameter : public IntegerParameter {

public:

	RelativeParameter(String *title, int steps, int initialStep, void (*onChange)(RelativeParameter *sender) = nullptr);
	~RelativeParameter();

	float relativeValue;

protected:

	virtual void notify();
};

#endif
