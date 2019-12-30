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
