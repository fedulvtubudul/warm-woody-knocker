#include "Storage.h"


Storage::Storage() {
    setValue(storedParameterScheme, 0);
}

Storage::~Storage() {
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
