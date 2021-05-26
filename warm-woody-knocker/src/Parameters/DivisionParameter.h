#ifndef DivisionParameter_h
#define DivisionParameter_h

#include "Arduino.h"
#include "Parameter.h"
#include "EnumParameter.h"


class Storage;


enum DivisionMode : int {
	divisionMode1to4,
	divisionMode1to8,
	divisionMode1to16,

	divisionModesCount
};


class DivisionParameter : public EnumParameter {

public:

	DivisionParameter(Storage *storage, void (*onChange)(DivisionParameter *sender) = nullptr);
	~DivisionParameter();

	virtual void stepBy(int stepValue);
	unsigned long subBeatDuration(unsigned long beatDuration);

private:

	DivisionParameter();

};

#endif
