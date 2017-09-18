// Core library for code-sense - IDE-based
#include "Arduino.h"
#include <LiquidCrystal.h>


#define ENCODER_A_INPUT 10
#define ENCODER_B_INPUT 11
#define ENCODER_BUTTON_INPUT 12

#define LED_OUTPUT LED_BUILTIN
#define ONBEAT_OUTPUT 8
#define OFFBEAT_OUTPUT 9

#define DEBOUNCE_LOOPS 40

#define MIN_TEMPO 30
#define MAX_TEMPO 300

#define BPM_TO_MICRO 60000000lu


// RS / E / D4 / D5 / D6 / D7
// RW pin to ground
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

unsigned int tempo = 60;
unsigned int beatCount = 0;
unsigned int subdivCount = 0;

// These values are in microseconds.
unsigned long lastOnbeatBeep = 0;
unsigned long lastOffbeatBeep = 0;
unsigned long onbeatBeepInterval = BPM_TO_MICRO / tempo;
unsigned long offbeatBeepInterval = BPM_TO_MICRO / tempo;
unsigned long onbeatBeepLength= 2000lu;
unsigned long offbeatBeepLength= 2000lu;

bool modeChanged = true;
bool valueChanged = true;

enum EditValueMode {
    editValueModeTempo,
    editValueModeSubdiv,
    editValueModeAccent,
    
    editValueModeMaxValue
  };
int editMode = editValueModeTempo;

enum SubdivMode {
    subdivMode1to4,
    subdivMode1to8,
    subdivMode1to16,
    
    subdivModeMaxValue
  };
int subdivMode = subdivMode1to4;

enum AccentMode {
    accentMode0,
    accentMode1,
    accentMode2,
    accentMode3,
    accentMode4,
    accentMode5,
    accentMode6,
    accentMode7,
    accentMode8,
    accentMode9,
    accentMode10,
    accentMode11,
    accentMode12,
    accentMode13,
    accentMode14,
    accentMode15,
    accentMode16,

    accentModeMaxValue,
    
    accentModeClave32,
    accentModeClave23,
  };
int accentMode = accentMode4;



void refreshBeepIntervals(void);
void beepIfNeeded(void);

int subdivMultiplier(void);
int accentedBeatMultiplier(void);

void handleInputEvents(void);
void handleEncoderTap(void);
void handleEncoderRotation(void);
void encoderTapAction(void);
void encoderSpinAction(const int valueDelta);
void deltaTempoValue(const int valueDelta);
void deltaSubdivValue (const int valueDelta);
void deltaAccentValue (const int valueDelta);

void printChanges(void);
void printMode(void);
void printValue(void);
void printTempoValue(void);
void printSubdivValue(void);
void printAccentValue(void);



void setup() {
  Serial.begin(115200);

  refreshBeepIntervals();

  lcd.begin(12, 2);

  pinMode(ENCODER_A_INPUT, INPUT_PULLUP);
  pinMode(ENCODER_B_INPUT, INPUT_PULLUP);
  pinMode(ENCODER_BUTTON_INPUT, INPUT_PULLUP);
  pinMode(LED_OUTPUT, OUTPUT);
  pinMode(ONBEAT_OUTPUT, OUTPUT);
  pinMode(OFFBEAT_OUTPUT, OUTPUT);
}

void loop() {
  beepIfNeeded();
  handleInputEvents();
  printChanges();
}

inline void beepIfNeeded() {
  unsigned long currentTime = micros();

  static bool onbeatBeepState = false;
  static bool offbeatBeepState = false;

//  if (currentTime - lastOnbeatBeep >= onbeatBeepInterval) {
////    digitalWrite(ONBEAT_OUTPUT, HIGH);
//    onbeatBeepState = true;
//    lastOnbeatBeep = currentTime;
//
//    int accentedBeats = accentedBeatMultiplier();
//    if (accentedBeats == 0) {
//      beatCount = 0;
//    }
//    else {
//      beatCount += 1;
//      beatCount %= accentedBeats;      
//    }
//        
//  }

  if (currentTime - lastOffbeatBeep >= offbeatBeepInterval) {
    lastOffbeatBeep = currentTime;

    subdivCount += 1;
    subdivCount %= subdivMultiplier();
    
    if (subdivCount == 0) {
		
      digitalWrite(ONBEAT_OUTPUT, HIGH);
      onbeatBeepState = true;
      lastOnbeatBeep = currentTime;
  
      int accentedBeats = accentedBeatMultiplier();
      if (accentedBeats == 0) {
        beatCount = 0;
      }
      else {
        beatCount += 1;
        beatCount %= accentedBeats;
      }
    }

    // Only perform off-beat tick on accent (beatCount = 0), or on off-beat (subdivCount != 0).
    if ((accentedBeatMultiplier() && beatCount == 0) || subdivCount != 0) {
      digitalWrite(OFFBEAT_OUTPUT, HIGH);
      offbeatBeepState = true;
    }

    lcd.setCursor(0, 0);
    lcd.print(beatCount);
    lcd.print(" / ");
    lcd.print(subdivCount);
    
  }
  
  if (onbeatBeepState && (currentTime - lastOnbeatBeep >= onbeatBeepLength)) {
    digitalWrite(ONBEAT_OUTPUT, LOW);
	
	long beeptime = currentTime - lastOffbeatBeep;
	char s[5] = {0, 0, 0, 0, 0};
	sprintf(s, "%d\n\r", beeptime);
	Serial.print(s);
	
    onbeatBeepState = false;
  }

  if (offbeatBeepState && (currentTime - lastOffbeatBeep >= offbeatBeepLength)) {
    digitalWrite(OFFBEAT_OUTPUT, LOW);
    offbeatBeepState = false;
  }
}

inline void printChanges(void) {
  if (modeChanged) {
    printMode();
    printValue();
    modeChanged = false;
  }

  if (valueChanged) {
    printValue();
    valueChanged = false;
  }
}

inline void printMode(void) {
    lcd.setCursor(0, 1);
    
    switch (editMode) {
        case editValueModeTempo: {
            lcd.print("TEMPO   ");
            break;
          }
        case editValueModeSubdiv: {
            lcd.print("SUBDIV  ");
            break;
          }
        case editValueModeAccent: {
            lcd.print("ACCENT  ");
            break;
          }
      }
}

void printValue() {
  lcd.setCursor(11 - 4, 1);
  lcd.print("    ");
  
  switch (editMode) {
      case editValueModeTempo: {
          printTempoValue();
          break;
        }
      case editValueModeSubdiv: {
          printSubdivValue();
          break;
        }
      case editValueModeAccent: {
          printAccentValue();
          break;
        }
    }
}

inline void printTempoValue() {
  int printOffset = 0;
  int valueDiv = tempo;
  while (valueDiv > 9) {
    ++printOffset;
    valueDiv /= 10;
  }
  
  lcd.setCursor(11 - printOffset, 1);
  lcd.print(tempo);
}

inline void printSubdivValue(void) {
  lcd.setCursor(11 - 3, 1);
  
  switch (subdivMode) {
      case subdivMode1to4: {
          lcd.print(" 1/4");
          break;
        }
      case subdivMode1to8: {
          lcd.print(" 1/8");
          break;
        }
      case subdivMode1to16: {
          lcd.print("1/16");
          break;
        }
    }
}

inline void printAccentValue(void) {
  lcd.setCursor(11 - 3, 1);
  
  switch (accentMode) {
      case accentModeClave32: {
          lcd.print("c3-2");
          break;
        }
      case accentModeClave23: {
          lcd.print("c2-3");
          break;
        }
      default: {
          int printOffset = 0;
          int valueDiv = accentMode;
          while (valueDiv > 9) {
            ++printOffset;
            valueDiv /= 10;
          }
          
          lcd.setCursor(11 - printOffset, 1);
          lcd.print(accentMode);
          break;
        }
    }
}

inline void handleInputEvents(void) {
  handleEncoderTap();
  handleEncoderRotation();
}

inline void handleEncoderTap(void) {
  static signed char prevInputState = 0;

  bool const inputState = !digitalRead(ENCODER_BUTTON_INPUT);

  if (inputState) {
    if (!prevInputState) {
      encoderTapAction();
    }
    prevInputState = DEBOUNCE_LOOPS;
  }
  else if (prevInputState > 0) {
    --prevInputState;
  }
}


inline void handleEncoderRotation(void) {
  static bool encoderLastStateA = HIGH;
  bool const encoderStateA = digitalRead(ENCODER_A_INPUT);
  bool const encoderStateB = digitalRead(ENCODER_B_INPUT);

  if (encoderStateA && !encoderLastStateA) {
    encoderSpinAction(encoderStateB ? -1 : 1);
  }

  encoderLastStateA = encoderStateA;
}

void encoderTapAction(void) {
  ++editMode %= editValueModeMaxValue;
  modeChanged = true;
}

void encoderSpinAction(const int valueDelta) {
  switch (editMode) {
      case editValueModeTempo: {
          deltaTempoValue(valueDelta);
          break;
        }
      case editValueModeSubdiv: {
          deltaSubdivValue(valueDelta);
          break;
        }
      case editValueModeAccent: {
          deltaAccentValue(valueDelta);
          break;
        }
    }  
}

inline void deltaTempoValue(const int valueDelta) {
  tempo += valueDelta;
  tempo = tempo >= MIN_TEMPO ? tempo : MIN_TEMPO;
  tempo = tempo <= MAX_TEMPO ? tempo : MAX_TEMPO;
  
  refreshBeepIntervals();
  
  // TODO: check if value changed.
  valueChanged = true;
}

inline void deltaSubdivValue (const int valueDelta) {
  subdivMode += valueDelta;
  subdivMode = subdivMode >= 0 ? subdivMode : 0;
  subdivMode = subdivMode < subdivModeMaxValue ? subdivMode : subdivModeMaxValue-1;
  
  // TODO: check if value changed.  
  valueChanged = true;

  refreshBeepIntervals();
}

inline void deltaAccentValue (const int valueDelta) {
  accentMode += valueDelta;
  accentMode = accentMode >= 0 ? accentMode : 0;
  accentMode = accentMode < accentModeMaxValue ? accentMode : accentModeMaxValue-1;

  // TODO: check if value changed.
  valueChanged = true;
}

void refreshBeepIntervals(void) {
  onbeatBeepInterval = BPM_TO_MICRO / tempo;
  offbeatBeepInterval = BPM_TO_MICRO / (tempo * subdivMultiplier());
}

int subdivMultiplier() {
  switch (subdivMode) {
    case subdivMode1to4: return 1;
    case subdivMode1to8: return 2;
    case subdivMode1to16: return 4;
  }

  return 1;
}

int accentedBeatMultiplier() {
  switch (accentMode) {
    case accentMode0: return 0;
    case accentMode1: return 1;
    case accentMode2: return 2;
    case accentMode3: return 3;
    case accentMode4: return 4;
    case accentMode5: return 5;
    case accentMode6: return 6;
    case accentMode7: return 7;
    case accentMode8: return 8;
    case accentMode9: return 9;
    case accentMode10: return 10;
    case accentMode11: return 11;
    case accentMode12: return 12;
    case accentMode13: return 13;
    case accentMode14: return 14;
    case accentMode15: return 15;
    case accentMode16: return 16;
  }

  return 1;
}

