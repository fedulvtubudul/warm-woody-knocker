#include "EnumParameter.h"
#include "../Storage/Storage.h"


EnumParameter::~EnumParameter() {
	
}

EnumParameter::EnumParameter(String *title, Storage *storage, StoredParameter parameter, int valuesCount, String *valueTitles, void (*onChange)(EnumParameter *sender)) :
	Parameter(title, storage, parameter, onChange),
	valuesCount(valuesCount),
	valueTitles(valueTitles) {
	
	int storedValue = 0;
	storage->getValue<int>(parameter, storedValue);
	storedValue = min(storedValue, valuesCount - 1);
	storedValue = max(storedValue, 0);
	value = storedValue;
}

void EnumParameter::stepBy(int stepValue) {
	value += stepValue + valuesCount;
	value %= valuesCount;

	storage->setValue(storedParameter, value);

	notify();
}


String EnumParameter::printableValue() {
	return valueTitles[value];
}

int EnumParameter::getRawValue() {
	return value;
}
