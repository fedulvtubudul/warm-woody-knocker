#ifndef Animation_h
#define Animation_h
#include <Arduino.h>


class LiquidCrystal;


class Animation {
	public:
		Animation(LiquidCrystal *lcd, int screenLine, int screenWidth);
		void step();
		
	private:
		LiquidCrystal *lcd;
		int currentState;
		int screenLine;
		int screenWidth;

		void printState(int state);
		void printBlankHalf();
		void printFilledHalf();
};

#endif
