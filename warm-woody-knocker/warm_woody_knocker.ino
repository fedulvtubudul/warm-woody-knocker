#include "Arduino.h"
#include <LiquidCrystal.h>

#include "src/Controls/Button.h"
#include "src/Controls/Encoder.h"

#include "src/Parameters/Parameter.h"
#include "src/Parameters/EnumParameter.h"
#include "src/Parameters/TempoParameter.h"
#include "src/Parameters/RelativeParameter.h"

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

unsigned long measureStart = 0;

boolean modeChanged = true;
boolean valueChanged = true;
boolean runningChanged = true;

int globalParametersCount;
Parameter **globalParameters;
EnumParameter *rhythmParameter;
TempoParameter *tempoParameter;
RelativeParameter *volumeParameter;
int currentParameterIndex = 0;
Parameter *currentParameter();

Player *player;

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

void buttonClickAction(void);
void buttonHoldAction(void);
void encoderSpinAction(SpinDirection direction);

void printChanges(void);
void printMode(void);
void printValue(void);
void printAccentValue(void);
void clearPendulum(uint8_t prevPosition, uint8_t newPosition);
void printPendulum(uint8_t prevPosition, uint8_t newPosition);

//U8G2_SSD1306_128X64_VCOMH0_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);


int positionX = 0;
int positionY = 0;

void setup() {
//	Serial.begin(115200);

	setupPlayer();
	setupRhythms();
	setupGlobalParameters();

  lcd.begin(LCD_LINE_WIDTH, LCD_LINES_COUNT);

	button = new Button(buttonPin, buttonClickThreshold, &buttonClickAction, buttonHoldThreshold, &buttonHoldAction);
	encoder = new Encoder(encoderPinA, encoderPinB, spinThreshold, &encoderSpinAction);
}

void setupPlayer() {
	volumeParameter = makeVolumeParameter();
	player = new Player(volumeParameter);
}

void setupRhythms() {
	tempoParameter = makeTempoParameter();

	rhythms[0] = new PatternRhythm(player, tempoParameter);
	rhythms[1] = new LinearRhythm(player, tempoParameter);

	currentRhythmIndex = 0;
	
	rhythmParameter = makeRhythmParameter();
}


void setupGlobalParameters() {
	globalParametersCount = 2;
	globalParameters = new Parameter*[globalParametersCount];
	globalParameters[0] = rhythmParameter;
	globalParameters[1] = volumeParameter;
}

RelativeParameter *makeVolumeParameter() {
	RelativeParameter *parameter = new RelativeParameter(new String("VOLUME"), 20, 3);
	return parameter;
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
			RHYTHMS_COUNT,
			titles,
			0,
			onRhythmChange
		);

	return parameter;
}

void onTempoChange(TempoParameter *sender) {
	// valueChanged = true;
}

TempoParameter *makeTempoParameter() {
	TempoParameter *parameter = new TempoParameter(onTempoChange);
	return parameter;
}

void loop() {
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

uint8_t const pendulumPositions = LCD_LINE_WIDTH - (PENDULUM_WIDTH - 1);
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

inline void printChanges(void) {
	if (modeChanged || valueChanged) {
		clearLine(1);
		printMode();
		printValue();
		modeChanged = false;
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
	lcd.setCursor(0, 1);
	lcd.print(*title);
}

void printValue() {
	String value = currentParameter()->printableValue();

	lcd.setCursor(LCD_LINE_WIDTH - value.length(), 1);
	lcd.print(value);
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
}

