#include "EnumParameter.h"


EnumParameter::~EnumParameter() {
	
}

EnumParameter::EnumParameter(String *title, Storage *storage, StoredParameter parameter, int valuesCount, String *valueTitles, int initialValue, void (*onChange)(EnumParameter *sender)) :
	Parameter(title, storage, parameter, onChange),
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
