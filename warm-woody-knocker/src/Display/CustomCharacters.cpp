#include "CustomCharacters.h"


static struct CustomCharacter millisecondCharacter = {
    .lcdAlias = 0,
    .stringAlias = '$',
    .glyphData = {
        B11010,
        B10101,
        B10101,
        B00000,
        B00110,
        B01100,
        B00110,
        B01100
    }
};

static struct CustomCharacter leftArrowCharacter = {
    .lcdAlias = 1,
    .stringAlias = '<',
    .glyphData = {
        B00000,
        B00010,
        B00110,
        B01110,
        B00110,
        B00010,
        B00000,
        B00000
    }
};

static struct CustomCharacter rightArrowCharacter = {
    .lcdAlias = 2,
    .stringAlias = '>',
    .glyphData = {
        B00000,
        B01000,
        B01100,
        B01110,
        B01100,
        B01000,
        B00000,
        B00000
    }
};
