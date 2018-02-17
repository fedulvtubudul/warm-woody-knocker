#include "EnumParameter.h"


EnumParameter::~EnumParameter() {
	
}

EnumParameter::EnumParameter(String *title, void (*onChange)(EnumParameter *sender), int valuesCount, String *valueTitles) :
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
