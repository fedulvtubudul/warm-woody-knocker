#ifndef Storage_h
#define Storage_h

#include "Arduino.h"
#include "StoredParameter.h"
#include <EEPROM.h>


class Storage {

public:
	Storage();
	virtual ~Storage();

    template<typename T>
    void Storage::getValue(StoredParameter parameter, T &value) {
        EEPROM.get<T>(eepromAddress(parameter), value);
    }

    template<typename T>
    void Storage::setValue(StoredParameter parameter, const T value) {
        EEPROM.put<T>(eepromAddress(parameter), value);
    }

private:
    int eepromAddress(StoredParameter parameter);
};

#endif
