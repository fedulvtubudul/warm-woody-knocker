#ifndef Animation_h
#define Animation_h
#include <Arduino.h>


class LiquidCrystal;


class Animation {
	public:
		Animation::Animation(LiquidCrystal *lcd, int screenLine, int screenWidth);
		void check(unsigned long now);
		void setTempo(unsigned long beatDuration);
		
	private:
		LiquidCrystal *lcd;
		unsigned long beatDuration;
		unsigned long beatStart;
		int currentState;
		int screenLine;
		int screenWidth;

		void printState(int state);
		void printBlankHalf();
		void printFilledHalf();
};

#endif
