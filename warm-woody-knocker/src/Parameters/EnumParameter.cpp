#include "EnumParameter.h"


EnumParameter::~EnumParameter() {
	
}

EnumParameter::EnumParameter(String *title, void (*onChange)(void), int valuesCount, String *valueTitles) :
	Parameter(title, onChange),
	valuesCount(valuesCount),
	valueTitles(valueTitles) {
}

void EnumParameter::stepBy(int stepValue) {
	currentValue += stepValue + valuesCount;
	currentValue %= valuesCount;

	notify();
}


String EnumParameter::printableValue() {
	return valueTitles[currentValue];
}

int EnumParameter::getRawValue() {
	return currentValue;
}
