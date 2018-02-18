#ifndef DivisionParameter_h
#define DivisionParameter_h

#include "Arduino.h"
#include "Parameter.h"
#include "EnumParameter.h"


enum DivisionMode : int {
	divisionMode1to4,
	divisionMode1to8,
	divisionMode1to16,

	divisionModesCount
};


class DivisionParameter : public EnumParameter {

public:

	DivisionParameter(void (*onChange)(DivisionParameter *sender));
	~DivisionParameter();

	virtual void stepBy(int stepValue);

private:

	DivisionParameter();

};

#endif