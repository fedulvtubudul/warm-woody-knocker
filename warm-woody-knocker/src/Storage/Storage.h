#ifndef Storage_h
#define Storage_h

#include "Arduino.h"
#include "StoredParameter.h"
#include "StoredData.h"
#include <EEPROM.h>


class Storage {

public:
	Storage();
	virtual ~Storage();

    template<typename T>
    void Storage::getValue(StoredParameter parameter, T &value) {
        switch (parameter) {
            case storedParameterScheme:
                value = currentValues.scheme;
                break;
            case storedParameterRhythm:
                value = currentValues.rhythm;
                break;
            case storedParameterVolume:
                value = currentValues.volume;
                break;
            case storedParameterTempo:
                value = currentValues.tempo;
                break;
            case storedParameterMeter:
                value = currentValues.meter;
                break;
            case storedParameterDivision:
                value = currentValues.division;
                break;
            case storedParameterPattern:
                value = currentValues.pattern;
                break;
        }
    }

    template<typename T>
    void Storage::setValue(StoredParameter parameter, const T value) {
        switch (parameter) {
            case storedParameterScheme:
                currentValues.scheme = value;
                break;
            case storedParameterRhythm:
                currentValues.rhythm = value;
                break;
            case storedParameterVolume:
                currentValues.volume = value;
                break;
            case storedParameterTempo:
                currentValues.tempo = value;
                break;
            case storedParameterMeter:
                currentValues.meter = value;
                break;
            case storedParameterDivision:
                currentValues.division = value;
                break;
            case storedParameterPattern:
                currentValues.pattern = value;
                break;
        }
    }

    void synchronize();

private:
    int eepromAddress(StoredParameter parameter);
    struct StoredData currentValues;
    struct StoredData savedValues;
};

#endif
