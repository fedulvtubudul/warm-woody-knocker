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
#include "src/Animation/Animation.h"
#include "src/Display/CustomCharacters.h"
#include "src/Storage/Storage.h"


#define LCD_LINE_WIDTH 12
#define LCD_LINES_COUNT 2
#define ANIMATION_WIDTH 1
#define ANIMATION_HEIGHT 2
int const scrollSymbolWidth = 1;
char emptyLine[LCD_LINE_WIDTH - ANIMATION_WIDTH];


Animation *animation;
Encoder *encoder;
Button *button;
Storage *storage;
uint8_t const encoderPinA = 10;
uint8_t const encoderPinB = 11;
uint8_t const buttonPin = 12;
uint32_t const spinThreshold = 5;
uint32_t const buttonClickThreshold = 40;
uint32_t const buttonHoldThreshold = 2000;


#define RHYTHMS_COUNT 2
Rhythm *rhythms[RHYTHMS_COUNT];
int currentRhythmIndex;

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


void buttonClickAction(void);
void buttonHoldAction(void);
void encoderSpinAction(SpinDirection direction);

void printChanges(void);
void printMode(void);
void printValue(void);
void printAccentValue(void);


void setup() {
	memset(emptyLine, (int)' ', LCD_LINE_WIDTH - ANIMATION_WIDTH);
	lcd.createChar(millisecondCharacter.lcdAlias, millisecondCharacter.glyphData);
	lcd.createChar(leftArrowCharacter.lcdAlias, leftArrowCharacter.glyphData);
	lcd.createChar(rightArrowCharacter.lcdAlias, rightArrowCharacter.glyphData);
	lcd.begin(LCD_LINE_WIDTH, LCD_LINES_COUNT);
	button = new Button(buttonPin, buttonClickThreshold, &buttonClickAction, buttonHoldThreshold, &buttonHoldAction);
	encoder = new Encoder(encoderPinA, encoderPinB, spinThreshold, &encoderSpinAction);
	animation = new Animation(&lcd, 0, 0, ANIMATION_WIDTH, ANIMATION_HEIGHT);
	storage = new Storage();
	setupPlayer();
	setupRhythms();
	setupGlobalParameters();
}

void setupPlayer() {
	volumeParameter = makeVolumeParameter();
	player = new Player(volumeParameter);
}

void setupRhythms() {
	tempoParameter = makeTempoParameter();
	onTempoChange(tempoParameter);

	rhythms[0] = new LinearRhythm(storage, player, tempoParameter, animation);
	rhythms[1] = new PatternRhythm(storage, player, tempoParameter, animation);

	rhythmParameter = makeRhythmParameter();
	currentRhythmIndex = rhythmParameter->getRawValue();
}


void setupGlobalParameters() {
	globalParametersCount = 2;
	globalParameters = new Parameter*[globalParametersCount];
	globalParameters[0] = rhythmParameter;
	globalParameters[1] = volumeParameter;
}

RelativeParameter *makeVolumeParameter() {
	RelativeParameter *parameter = new RelativeParameter(new String("VOLUME"), storage, storedParameterVolume, 20);
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
			storage,
			storedParameterRhythm,
			RHYTHMS_COUNT,
			titles,
			onRhythmChange
		);

	return parameter;
}

void onTempoChange(TempoParameter *sender) {
}

TempoParameter *makeTempoParameter() {
	TempoParameter *parameter = new TempoParameter(storage, onTempoChange);
	return parameter;
}

void loop() {
	if (running) {
		unsigned long now = micros();
		rhythms[currentRhythmIndex]->check(now);
	}
	button->check();
	encoder->check();
	printChanges();
}

inline void printChanges(void) {
	if (modeChanged || valueChanged) {
		printMode();
		printValue();
		modeChanged = false;
		valueChanged = false;
	}
}

void clearLine(uint8_t line) {
	lcd.setCursor(ANIMATION_WIDTH, line);
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
	clearLine(0);
	String *title = currentParameter()->getTitle();
	lcd.setCursor(ANIMATION_WIDTH + scrollSymbolWidth, 0);
	lcd.print(*title);
	printScrollSymbol(0);
}

void printScrollSymbol(int activeLine) {
	for (int line = 0; line < LCD_LINES_COUNT; line++) {
		lcd.setCursor(ANIMATION_WIDTH, line);
		for (int i = 0; i < scrollSymbolWidth; i++) {
			char symbol = line == activeLine ? leftArrowCharacter.lcdAlias : ' ';
			lcd.print(symbol);
		}
		lcd.setCursor(LCD_LINE_WIDTH - scrollSymbolWidth, line);
		for (int i = 0; i < scrollSymbolWidth; i++) {
			char symbol = line == activeLine ? rightArrowCharacter.lcdAlias : ' ';
			lcd.print(symbol);
		}
	}
}

void printValue() {
	clearLine(1);
	String value = currentParameter()->printableValue();
	value.replace(millisecondCharacter.stringAlias, millisecondCharacter.lcdAlias);
	lcd.setCursor(ANIMATION_WIDTH + scrollSymbolWidth, 1);
	lcd.print(value);
}

void buttonClickAction(void) {
	int parametersCount = globalParametersCount + rhythms[currentRhythmIndex]->getParametersCount();
	currentParameterIndex = (currentParameterIndex + 1) % parametersCount;

	modeChanged = true;
}

void buttonHoldAction(void) {
	running = !running;
	storage->synchronize();
	runningChanged = true;
}

void encoderSpinAction(SpinDirection direction) {
	int valueDelta = direction == spinDirectionCW ? 1 : -1;
	currentParameter()->stepBy(valueDelta);

	valueChanged = true;
}

