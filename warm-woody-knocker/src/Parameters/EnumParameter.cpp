#include "EnumParameter.h"


EnumParameter::~EnumParameter() {
	
}

EnumParameter::EnumParameter(String *title, void (*onChange)(EnumParameter *sender), int valuesCount, String *valueTitles, int initialValue) :
	Parameter(title, onChange),
	valuesCount(valuesCount),
	valueTitles(valueTitles),
	value(initialValue) {
	
}

void EnumParameter::stepBy(int stepValue) {
	value += stepValue + valuesCount;
	value %= valuesCount;

	notify();
}


String EnumParameter::printableValue() {
	return valueTitles[value];
}

int EnumParameter::getRawValue() {
	return value;
}
