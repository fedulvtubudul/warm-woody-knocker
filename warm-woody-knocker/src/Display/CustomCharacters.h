#ifndef CustomCharacter_h
#define CustomCharacter_h

#include "Arduino.h"


struct CustomCharacter {
    byte lcdAlias;
    char stringAlias;
    byte glyphData[8];
};

extern struct CustomCharacter millisecondCharacter;

#endif
