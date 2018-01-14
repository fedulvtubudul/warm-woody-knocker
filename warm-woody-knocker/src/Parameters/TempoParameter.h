#ifndef TempoParameter_h
#define TempoParameter_h

#include "Arduino.h"
#include "IntegerParameter.h"


class TempoParameter : public IntegerParameter {

public:

	TempoParameter(void (*onChange)(void));
	~TempoParameter();

};

#endif
