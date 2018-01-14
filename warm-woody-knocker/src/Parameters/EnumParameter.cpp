#include "EnumParameter.h"


EnumParameter::~EnumParameter() {
	
}

EnumParameter::EnumParameter(String *title, int valuesCount, String *valueTitles) :
	Parameter(title),
	valuesCount(valuesCount),
	valueTitles(valueTitles) {
}

void EnumParameter::stepBy(int stepValue) {
	currentValue += stepValue + valuesCount;
	currentValue %= valuesCount;
}


String EnumParameter::printableValue() {
	return valueTitles[currentValue];
}
