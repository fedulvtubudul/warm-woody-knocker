#include "Pattern.h"


Pattern makeClavePattern() {
	int length = 16;

	Pattern pattern = {
		title: String("Clave"),
		meter: 8,
		length: length,
		lowChannelValues: new SoundLevel[length],
		highChannelValues: new SoundLevel[length]
	};

	int i = 0;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;

	i = 0;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;

	return pattern;
}

Pattern makeBembePattern() {
	int length = 12;

	Pattern pattern = {
		title: String("Bembe"),
		meter: 12,
		length: length,
		lowChannelValues: new SoundLevel[length],
		highChannelValues: new SoundLevel[length]
	};

	int i = 0;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::low;

	i = 0;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;

	return pattern;
}

Pattern makeSongoPattern() {
	int length = 16;

	Pattern pattern = {
		title: String("Songo"),
		meter: 16,
		length: length,
		lowChannelValues: new SoundLevel[length],
		highChannelValues: new SoundLevel[length]
	};

	int i = 0;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;

	i = 0;
	pattern.highChannelValues[i++] = SoundLevel::high;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::low;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::low;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::low;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;


	return pattern;
}

Pattern makeSaiidiPattern() {
	int length = 8;

	Pattern pattern = {
		title: String("Saiidi"),
		meter: 8,
		length: length,
		lowChannelValues: new SoundLevel[length],
		highChannelValues: new SoundLevel[length]
	};

	int i = 0;
	pattern.lowChannelValues[i++] = SoundLevel::high;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::high;
	pattern.lowChannelValues[i++] = SoundLevel::high;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;

	i = 0;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;


	return pattern;
}

Pattern makeSwing3Pattern() {
	int length = 9;

	Pattern pattern = {
		title: String("Swing 3"),
		meter: 12,
		length: length,
		lowChannelValues: new SoundLevel[length],
		highChannelValues: new SoundLevel[length]
	};

	int i = 0;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::high;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::high;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::high;

	i = 0;
	pattern.highChannelValues[i++] = SoundLevel::high;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;

	return pattern;
}

Pattern makeSwing4Pattern() {
	int length = 12;

	Pattern pattern = {
		title: String("Swing 4"),
		meter: 12,
		length: length,
		lowChannelValues: new SoundLevel[length],
		highChannelValues: new SoundLevel[length]
	};

	int i = 0;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::high;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::high;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::high;
	pattern.lowChannelValues[i++] = SoundLevel::low;
	pattern.lowChannelValues[i++] = SoundLevel::no;
	pattern.lowChannelValues[i++] = SoundLevel::high;

	i = 0;
	pattern.highChannelValues[i++] = SoundLevel::high;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;
	pattern.highChannelValues[i++] = SoundLevel::no;

	return pattern;
}
