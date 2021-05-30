#include "Storage.h"


Storage::Storage() {
    EEPROM.get<int>(eepromAddress(storedParameterScheme), savedValues.scheme);
    EEPROM.get<int>(eepromAddress(storedParameterRhythm), savedValues.rhythm);
    EEPROM.get<int>(eepromAddress(storedParameterVolume), savedValues.volume);
    EEPROM.get<int>(eepromAddress(storedParameterTempo), savedValues.tempo);
    EEPROM.get<int>(eepromAddress(storedParameterMeter), savedValues.meter);
    EEPROM.get<int>(eepromAddress(storedParameterDivision), savedValues.division);
    EEPROM.get<int>(eepromAddress(storedParameterPattern), savedValues.pattern);

    currentValues = savedValues;
}

Storage::~Storage() {
}

void Storage::synchronize() {
    if (currentValues.scheme != savedValues.scheme) {
        EEPROM.put<int>(eepromAddress(storedParameterScheme), currentValues.scheme);        
    }

    if (currentValues.rhythm != savedValues.rhythm) {
        EEPROM.put<int>(eepromAddress(storedParameterRhythm), currentValues.rhythm);
    }

    if (currentValues.volume != savedValues.volume) {
        EEPROM.put<int>(eepromAddress(storedParameterVolume), currentValues.volume);
    }

    if (currentValues.tempo != savedValues.tempo) {
        EEPROM.put<int>(eepromAddress(storedParameterTempo), currentValues.tempo);
    }

    if (currentValues.meter != savedValues.meter) {
        EEPROM.put<int>(eepromAddress(storedParameterMeter), currentValues.meter);
    }

    if (currentValues.division != savedValues.division) {
        EEPROM.put<int>(eepromAddress(storedParameterDivision), currentValues.division);
    }

    if (currentValues.pattern != savedValues.pattern) {
        EEPROM.put<int>(eepromAddress(storedParameterPattern), currentValues.pattern);
    }

    savedValues = currentValues;
}

int Storage::eepromAddress(StoredParameter parameter) {
    switch (parameter) {
        case storedParameterScheme: return 0x0000;
        case storedParameterRhythm: return 0x0002;
        case storedParameterVolume: return 0x0004;
        case storedParameterTempo: return 0x0006;
        case storedParameterMeter: return 0x0008;
        case storedParameterDivision: return 0x000A;
        case storedParameterPattern: return 0x000C;
        default: return 0xFFFF;
    }
}
