#ifndef TempoParameter_h
#define TempoParameter_h

#include "Arduino.h"
#include "IntegerParameter.h"


class Storage;


class TempoParameter : public IntegerParameter {

public:

	TempoParameter(Storage *storage, void (*onChange)(TempoParameter *sender) = nullptr);
	~TempoParameter();

	virtual String printableValue();
	void setTempoWithBeatDuration(unsigned long beatDuration);

	int minTempo;
	int maxTempo;
	unsigned long beatDuration;

protected:

	virtual void notify();
};

#endif
