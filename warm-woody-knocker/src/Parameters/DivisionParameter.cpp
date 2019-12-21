#include "DivisionParameter.h"


DivisionParameter::~DivisionParameter() {
	
}

DivisionParameter::DivisionParameter(void (*onChange)(DivisionParameter *sender)) :
	EnumParameter(
		new String("DIVISION"),
		divisionModesCount,
		new String[divisionModesCount],
		divisionMode1to4,
		onChange
	) {
	valueTitles[divisionMode1to4] = String("1/4");
	valueTitles[divisionMode1to8] = String("1/8");
	valueTitles[divisionMode1to16] = String("1/16");
}

void DivisionParameter::stepBy(int stepValue) {
	value += stepValue;
	value = value > 0 ? value : 0;
	value = value < divisionModesCount ? value : (divisionModesCount-1);

	notify();
}
