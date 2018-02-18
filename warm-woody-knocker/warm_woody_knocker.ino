#include "Arduino.h"
#include <LiquidCrystal.h>

#include "src/Controls/Button.h"
#include "src/Controls/Encoder.h"

#include "src/Parameters/Parameter.h"
#include "src/Parameters/EnumParameter.h"
#include "src/Parameters/TempoParameter.h"

#include "src/Rhythm/Rhythm.h"
#include "src/Rhythm/PatternRhythm.h"
#include "src/Rhythm/LinearRhythm.h"

#include "src/Player/Player.h"


//#include <U8g2lib.h>
//
//#define U8X8_HAVE_HW_I2C
//#ifdef U8X8_HAVE_HW_I2C
//  #include <Wire.h>
//#endif


#define LED_OUTPUT LED_BUILTIN
#define LCD_LINE_WIDTH 16
#define LCD_LINES_COUNT 2
#define ONBEAT_OUTPUT 8
#define OFFBEAT_OUTPUT 9


Encoder *encoder;
Button *button;
uint8_t const encoderPinA = 10;
uint8_t const encoderPinB = 11;
uint8_t const buttonPin = 12;
uint32_t const spinThreshold = 5;
uint32_t const buttonClickThreshold = 40;
uint32_t const buttonHoldThreshold = 2000;


long const volumeValueMultiplier = 100;

float const onbeatVolumeValueMultiplier = 1.5f;
float const subdivVolumeValueMultiplier = 0.5f;


#define RHYTHMS_COUNT 2
Rhythm *rhythms[RHYTHMS_COUNT];
int currentRhythmIndex;

#define MIN_TEMPO 15
#define MAX_TEMPO 300

#define BPM_TO_MICRO 60000000lu


// RS / E / D4 / D5 / D6 / D7
// RW pin to ground
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


unsigned int tempo = 120;
unsigned int beatCount = 0;
unsigned int subdivCount = 0;
boolean running = true;

// These values are in microseconds.
unsigned long lastOnbeatBeep = 0;
unsigned long lastOffbeatBeep = 0;
unsigned long lastSubdivBeep = 0;

unsigned long measureStart = 0;
double measurePosition = 0;
unsigned long onbeatBeepInterval;
unsigned long offbeatBeepInterval;
unsigned long subdivBeepInterval;

unsigned long onbeatBeepLength;
unsigned long offbeatBeepLength;
unsigned long subdivBeepLength;

boolean modeChanged = true;
boolean valueChanged = true;
boolean runningChanged = true;

int globalParametersCount;
Parameter **globalParameters;
EnumParameter *rhythmParameter;
TempoParameter *tempoParameter;
int currentParameterIndex = 0;
Parameter *currentParameter();

Player *player;

// enum EditValueMode {
// 	editValueModeRhythm,
//     editValueModeVolume,

// 	editValueModeTempo,
//     editValueModeSubdiv,
//     editValueModeAccent,

    
//     editValueModeMaxValue
//   };
// int editMode = editValueModeRhythm;

enum SubdivMode {
    subdivMode1to4,
    subdivMode1to8,
    subdivMode1to16,
    
    subdivModeMaxValue
  };
int subdivMode = subdivMode1to8;

int volumeValue = 7;
int const volumeValueMaxValue = 30;

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
	
    accentModeClave32,
    accentModeClave23,

    accentModeMaxValue,
  };
int accentMode = accentMode4;



void refreshBeepIntervals(void);
void beepIfNeeded(void);

uint8_t positionForPendulumState(uint8_t state);
void movePendulumIfNeeded(void);

int subdivMultiplier(void);
int accentedBeatMultiplier(void);

void buttonClickAction(void);
void buttonHoldAction(void);
void encoderSpinAction(SpinDirection direction);

void encoderSpinAction(const int valueDelta);
void deltaTempoValue(const int valueDelta);
void deltaRhythmValue(const int valueDelta);
void deltaSubdivValue (const int valueDelta);
void deltaAccentValue (const int valueDelta);
void deltaVolumeValue (const int valueDelta);

void printChanges(void);
void printMode(void);
void printValue(void);
void printTempoValue(void);
void printSubdivValue(void);
void printAccentValue(void);
void printVolumeValue(void);
void clearPendulum(uint8_t prevPosition, uint8_t newPosition);
void printPendulum(uint8_t prevPosition, uint8_t newPosition);

//U8G2_SSD1306_128X64_VCOMH0_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);


int positionX = 0;
int positionY = 0;

void setup() {
	Serial.begin(115200);

//  u8x8.begin();
//  u8x8.home();
//
//  u8x8.setContrast(80);
//  u8x8.clear();
//
//  u8x8.setCursor(0, 0);
////  u8x8.inverse();
////  u8x8.setFont(u8x8_font_pxplusibmcga_u);
//  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);
//
//
//  u8x8.print("1234567890123456");

	setupPlayer();
	setupRhythms();
	setupGlobalParameters();

  refreshBeepIntervals();

//  u8g2.begin();
//  u8g2.setContrast(80);
//  u8g2.setDrawColor(1);
//  u8g2.setFont(u8g2_font_logisoso16_tn);


  lcd.begin(LCD_LINE_WIDTH, LCD_LINES_COUNT);

	button = new Button(buttonPin, buttonClickThreshold, &buttonClickAction, buttonHoldThreshold, &buttonHoldAction);
	encoder = new Encoder(encoderPinA, encoderPinB, spinThreshold, &encoderSpinAction);

  pinMode(LED_OUTPUT, OUTPUT);
  pinMode(ONBEAT_OUTPUT, OUTPUT);
  pinMode(OFFBEAT_OUTPUT, OUTPUT);
}

void setupPlayer() {
	player = new Player();
}

void setupRhythms() {
	tempoParameter = makeTempoParameter();

	rhythms[0] = new PatternRhythm(player);
	rhythms[1] = new LinearRhythm(player, tempoParameter);

	currentRhythmIndex = 0;
}


void setupGlobalParameters() {
	globalParametersCount = 1;
	globalParameters = new Parameter*[globalParametersCount];

	rhythmParameter = makeRhythmParameter();
	globalParameters[0] = rhythmParameter;
}

void onRhythmChange(EnumParameter *sender) {
	currentRhythmIndex = sender->getRawValue();
}

EnumParameter *makeRhythmParameter() {
	String *titles = new String[RHYTHMS_COUNT];
	for (int i = 0; i < RHYTHMS_COUNT; ++i) {
		titles[i] = rhythms[i]->title();
	}

	EnumParameter *parameter = new EnumParameter(
			new String("RHYTHM"),
			onRhythmChange,
			RHYTHMS_COUNT,
			titles,
			0
		);

	return parameter;
}

TempoParameter *makeTempoParameter() {
	TempoParameter *parameter = new TempoParameter(nullptr);
	return parameter;
}

void drawValue() {
//	char cs[16];
//	sprintf(cs, "%d %d", positionX, positionY);
//    u8g2.drawStr(30, 50, cs);
}

void drawCursor() {
//	u8g2.drawPixel(0, 0);
//	u8g2.drawPixel(positionX, positionY);
}

void loop() {
//	u8g2.clearBuffer();
//	drawCursor();
//	drawValue();
//	u8g2.sendBuffer();
	
//	char read = Serial.read();
//	if (read == 'w') {
//		accentMode -= 1;
//	} else if (read == 'a') {
//		tempo -= 1;
//	} else if (read == 's') {
//		accentMode += 1;
//	} else if (read == 'd') {
//		tempo += 1;
//	}

//   beepIfNeeded();
	
	unsigned long now = micros();
	rhythms[currentRhythmIndex]->check(now);

  movePendulumIfNeeded();

	button->check();
	encoder->check();
	player->check(now);

  printChanges();
}


#define PENDULUM_LINE 0
#define PENDULUM_WIDTH 4
uint8_t pendulumPosition = PENDULUM_WIDTH;

#if 1
	uint8_t const pendulumPositions = LCD_LINE_WIDTH - (PENDULUM_WIDTH - 1);
#else
	uint8_t const pendulumPositions = 128 - (PENDULUM_WIDTH - 1);
#endif

uint8_t const pendulumStates = pendulumPositions * 2 - 2;

void movePendulumIfNeeded() {
  unsigned long currentTime = micros();
  unsigned long measureTime = currentTime - measureStart;
  unsigned long measureLength = BPM_TO_MICRO / tempo;

  unsigned long pendulumMoveInterval = 2 * (float)measureLength / (float)pendulumStates;
	
  uint8_t neededState = measureTime / pendulumMoveInterval;
  uint8_t neededPosition = positionForPendulumState(neededState);
	
  if (pendulumPosition != neededPosition) {
    clearPendulum(pendulumPosition, neededPosition);
	printPendulum(pendulumPosition, neededPosition);
	pendulumPosition = neededPosition;
//	u8g2.sendBuffer();
  }
}

uint8_t positionForPendulumState(uint8_t state) {
  state = state % pendulumStates;
  bool reverse = state >= pendulumPositions;
	
  uint8_t position;
  if (reverse) {
    position = pendulumStates - state;
  } else {
    position = state;
  }
	
  return position;
}

void clearPendulum(uint8_t prevPosition, uint8_t newPosition) {
  // -->
  if (prevPosition < newPosition) {
	  #if 1
	  lcd.setCursor(prevPosition, PENDULUM_LINE);
	  for (uint8_t i = prevPosition; i < newPosition; ++i) {
	    lcd.print((char)32);
	  }
	  #else
		  u8g2.setDrawColor(0);
		  u8g2.drawBox(prevPosition, 0, newPosition-prevPosition, 16);
	  #endif
  }
	
  // <--
  else if (prevPosition > newPosition) {
	  #if 1
	  lcd.setCursor(newPosition + PENDULUM_WIDTH, PENDULUM_LINE);
	  for (uint8_t i = newPosition; i < prevPosition; ++i) {
	    lcd.print((char)32);
	  }
	  #else
		  u8g2.setDrawColor(0);
		  u8g2.drawBox(newPosition+PENDULUM_WIDTH, 0, prevPosition-newPosition, 16);
	  #endif
  }
}

void printPendulum(uint8_t prevPosition, uint8_t newPosition) {
  // -->
  if (prevPosition < newPosition) {
	  #if 1
	  lcd.setCursor(prevPosition + PENDULUM_WIDTH, PENDULUM_LINE);
	  for (uint8_t i = prevPosition; i < newPosition; ++i) {
	    lcd.print((char)255);
	  }
	  #else
		  u8g2.setDrawColor(1);
		  u8g2.drawBox(newPosition, 0, PENDULUM_WIDTH, 16);
	  #endif
  }
	
  // <--
  else if (prevPosition > newPosition) {
	  #if 1
	  lcd.setCursor(newPosition, PENDULUM_LINE);
	  for (uint8_t i = newPosition; i < prevPosition; ++i) {
	    lcd.print((char)255);
	  }
	  #else
		  u8g2.setDrawColor(1);
		  u8g2.drawBox(newPosition, 0, PENDULUM_WIDTH, 16);
	  #endif
  }
}

static bool onbeatBeepState = false;
static bool offbeatBeepState = false;

//void stopBeepIfNeeded(unsigned long currentTime) {
//	bool m = false;
//
//  if (onbeatBeepState && (currentTime - lastOnbeatBeep >= onbeatBeepLength)) {
//    digitalWrite(ONBEAT_OUTPUT, LOW);
//    onbeatBeepState = false;
//
////	Serial.print("(+)");
//	m = true;
//  }
//
//  if (offbeatBeepState && (currentTime - lastOffbeatBeep >= offbeatBeepLength)) {
//    digitalWrite(OFFBEAT_OUTPUT, LOW);
//    offbeatBeepState = false;
//
////	Serial.print("(-)");
//  }
//
////  if (m) {
////  	long beeptime = currentTime - lastOffbeatBeep;
////	char s[5] = {0, 0, 0, 0, 0};
////	sprintf(s, "%ld\n\r", beeptime);
////	Serial.print(s);
////  }
//}

void startBeepIfNeeded(unsigned long currentTime) {
  unsigned long timeInMeasure = currentTime - measureStart;
  measurePosition = timeInMeasure / onbeatBeepInterval;

	if (currentTime - lastOffbeatBeep >= offbeatBeepInterval) {
		lastOffbeatBeep = currentTime;
		lastSubdivBeep = currentTime;
		
		int accentedBeats = accentedBeatMultiplier();
		if (accentedBeats == 0) {
			beatCount = 0;
			measureStart = currentTime;
		}
		else {
			beatCount += 1;
			beatCount %= accentedBeats;
			
			if (beatCount == 0) {
				measureStart = currentTime;
			}
		}


		digitalWrite(ONBEAT_OUTPUT, HIGH);
		onbeatBeepState = true;


		if (beatCount == 0) {
			lastOnbeatBeep = currentTime;
			delayMicroseconds(onbeatBeepLength);
		} else {
			delayMicroseconds(offbeatBeepLength);
		}
		
		currentTime = micros();
		digitalWrite(ONBEAT_OUTPUT, LOW);
		onbeatBeepState = false;
    } else if (currentTime - lastSubdivBeep >= subdivBeepInterval) {
		lastSubdivBeep = currentTime;
		subdivCount += 1;
		subdivCount %= subdivMultiplier();
		
		digitalWrite(OFFBEAT_OUTPUT, HIGH);
		offbeatBeepState = true;
		delayMicroseconds(offbeatBeepLength);
		currentTime = micros();
		digitalWrite(OFFBEAT_OUTPUT, LOW);
		offbeatBeepState = false;
	}

//    // Only perform off-beat tick on accent (beatCount = 0), or on off-beat (subdivCount != 0).
//    if ((accentedBeatMultiplier() && beatCount == 0) || subdivCount != 0) {
////	  Serial.print("-");
//      digitalWrite(OFFBEAT_OUTPUT, HIGH);
//      offbeatBeepState = true;
//
//
//	  delayMicroseconds(offbeatBeepLength);
//
//	  currentTime = micros();
//	  digitalWrite(OFFBEAT_OUTPUT, LOW);
//	  offbeatBeepState = false;
//
////		long beeptime = currentTime - lastOffbeatBeep;
////		char s[5] = {0, 0, 0, 0, 0};
////		sprintf(s, "-%ld\n\r", beeptime);
////		Serial.print(s);
//
//    }
//  }
}

inline void beepIfNeeded() {
  unsigned long currentTime = micros();
//  stopBeepIfNeeded(currentTime);
  startBeepIfNeeded(currentTime);

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

void clearLine(uint8_t line) {
	lcd.setCursor(0, line);
	char emptyLine[LCD_LINE_WIDTH];
	memset(emptyLine, (int)' ', LCD_LINE_WIDTH);
	lcd.write(emptyLine);
}

Parameter *currentParameter() {
	if (currentParameterIndex < globalParametersCount) {
		return globalParameters[currentParameterIndex];
	} else {
		int rhythmParameterIndex = currentParameterIndex - globalParametersCount;
		return rhythms[currentRhythmIndex]->getParameter(rhythmParameterIndex);
	}
}

void printMode(void) {
	String *title = currentParameter()->getTitle();

	clearLine(1);
	lcd.setCursor(0, 1);
	lcd.print(*title);

	// switch (editMode) {
	// 	case editValueModeRhythm: {
    //         lcd.print("RHYTHM");
    //         break;
    //       }
    //     case editValueModeTempo: {
    //         lcd.print("TEMPO");
    //         break;
    //       }
    //     case editValueModeSubdiv: {
    //         lcd.print("SUBDIV");
    //         break;
    //       }
    //     case editValueModeAccent: {
    //         lcd.print("ACCENT");
    //         break;
    //       }
    //     case editValueModeVolume: {
    //         lcd.print("VOLUME");
    //         break;
    //       }
    //   }
}

void printValue() {
//   lcd.setCursor(LCD_LINE_WIDTH-1 - 4, 1);
//   lcd.print("    ");

	String value = currentParameter()->printableValue();

	// clearLine(1);
	// lcd.rightToLeft();
	lcd.setCursor(LCD_LINE_WIDTH - value.length(), 1);
	lcd.print(value);
	// lcd.leftToRight();

//   switch (editMode) {
// 	  case editValueModeRhythm: {
//           printRhythmValue();
//           break;
//         }
//       case editValueModeTempo: {
//           printTempoValue();
//           break;
//         }
//       case editValueModeSubdiv: {
//           printSubdivValue();
//           break;
//         }
//       case editValueModeAccent: {
//           printAccentValue();
//           break;
//         }
//       case editValueModeVolume: {
//           printVolumeValue();
//           break;
//         }
//     }
}

inline void printRhythmValue() {
	Rhythm *rhythm = rhythms[currentRhythmIndex];
	int printOffset = rhythm->title().length();
	lcd.setCursor(LCD_LINE_WIDTH - printOffset, 1);
	lcd.print(rhythm->title());
}

inline void printTempoValue() {
  int printOffset = 0;
  int valueDiv = tempo;
  while (valueDiv > 9) {
    ++printOffset;
    valueDiv /= 10;
  }
  
  lcd.setCursor(LCD_LINE_WIDTH-1 - printOffset, 1);
  lcd.print(tempo);
}

inline void printSubdivValue(void) {
  lcd.setCursor(LCD_LINE_WIDTH-1 - 3, 1);
  
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

inline void printVolumeValue(void) {
  lcd.setCursor(LCD_LINE_WIDTH-3, 1);
  lcd.print("   ");
	
  int printOffset = 0;
  int valueDiv = tempo;
  while (valueDiv > 9) {
    ++printOffset;
    valueDiv /= 10;
  }
	
  lcd.setCursor(LCD_LINE_WIDTH-1 - printOffset, 1);
  lcd.print(volumeValue);
}

inline void printAccentValue(void) {
  lcd.setCursor(LCD_LINE_WIDTH-1 - 3, 1);
  
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
          
          lcd.setCursor(LCD_LINE_WIDTH-1 - printOffset, 1);
          lcd.print(accentMode);
          break;
        }
    }
}

void buttonClickAction(void) {
	int parametersCount = globalParametersCount + rhythms[currentRhythmIndex]->getParametersCount();
	currentParameterIndex = (currentParameterIndex + 1) % parametersCount;

	modeChanged = true;
	
	Rhythm *r = rhythms[currentRhythmIndex];
	int rpc = r->getParametersCount();


	Serial.println(parametersCount);
	
	Serial.print("rpc = ");
	Serial.println(rpc);

	Serial.println(currentParameterIndex);


}

void buttonHoldAction(void) {
	running = !running;
	runningChanged = true;
}

void encoderSpinAction(SpinDirection direction) {
	int valueDelta = direction == spinDirectionCW ? 1 : -1;
	currentParameter()->stepBy(valueDelta);

	valueChanged = true;
	printChanges();
//   switch (editMode) {
// 	  case editValueModeRhythm: {
// 		  deltaRhythmValue(valueDelta);
// 		  break;
// 	  }
//       case editValueModeTempo: {
//           deltaTempoValue(valueDelta);
//           break;
//         }
//       case editValueModeSubdiv: {
//           deltaSubdivValue(valueDelta);
//           break;
//         }
//       case editValueModeAccent: {
//           deltaAccentValue(valueDelta);
//           break;
//         }
// 	  case editValueModeVolume: {
// 		  deltaVolumeValue(valueDelta);
// 		  break;
// 	  }
//     }  
}

inline void refreshMeasurePositionFromTempo(unsigned int oldTempo) {
	unsigned long currentTime = micros();
	measureStart = currentTime - measurePosition * onbeatBeepInterval;
}

inline void deltaRhythmValue(const int valueDelta) {
	int oldRhythm = currentRhythmIndex;

	currentRhythmIndex += valueDelta + RHYTHMS_COUNT;
	currentRhythmIndex %= RHYTHMS_COUNT;

	valueChanged = currentRhythmIndex != oldRhythm;

	if (valueChanged) {
		rhythms[currentRhythmIndex]->resetState();
	}
}

inline void deltaTempoValue(const int valueDelta) {
  unsigned int oldTempo = tempo;

  tempo += valueDelta;
  tempo = tempo >= MIN_TEMPO ? tempo : MIN_TEMPO;
  tempo = tempo <= MAX_TEMPO ? tempo : MAX_TEMPO;
  
  valueChanged = tempo != oldTempo;
  if (valueChanged) {
    refreshBeepIntervals();
    refreshMeasurePositionFromTempo(oldTempo);
  }
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

inline void deltaVolumeValue (const int valueDelta) {
  volumeValue += valueDelta;
  volumeValue = volumeValue >= 0 ? volumeValue : 0;
  volumeValue = volumeValue < volumeValueMaxValue ? volumeValue : volumeValueMaxValue - 1;

  refreshBeepIntervals();

  // TODO: check if value changed.
  valueChanged = true;
}


void refreshBeepIntervals(void) {
	onbeatBeepInterval = accentedBeatMultiplier() * BPM_TO_MICRO / tempo;
	offbeatBeepInterval = BPM_TO_MICRO / tempo;
	subdivBeepInterval = BPM_TO_MICRO / (tempo * subdivMultiplier());
	
	long unsigned normalValue = volumeValue * volumeValueMultiplier;
	
	onbeatBeepLength = onbeatVolumeValueMultiplier * normalValue;
	offbeatBeepLength = normalValue;
	subdivBeepLength = subdivVolumeValueMultiplier * normalValue;
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

