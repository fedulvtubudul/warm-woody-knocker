#include "DivisionParameter.h"
#include "EnumParameter.h"


DivisionParameter::~DivisionParameter() {
	
}

DivisionParameter::DivisionParameter(Storage *storage, void (*onChange)(DivisionParameter *sender)) :
	EnumParameter(
		new String("DIVISION"),
		storage,
		storedParameterDivision,
		divisionModesCount,
		new String[divisionModesCount],
		divisionMode1to4,
		onChange
	) {
	valueTitles[divisionMode1to4] = String("1/4");
	valueTitles[divisionMode1to8] = String("1/8");
	valueTitles[divisionMode1to16] = String("1/16");
}

unsigned long DivisionParameter::subBeatDuration(unsigned long beatDuration) {
	switch (value) {
		case DivisionMode::divisionMode1to4:
			return beatDuration;
		case DivisionMode::divisionMode1to8:
			return beatDuration / 2;
		case DivisionMode::divisionMode1to16:
			return beatDuration / 4;
	}

	return beatDuration;
}
