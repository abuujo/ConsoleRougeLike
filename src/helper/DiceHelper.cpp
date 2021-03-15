#include "DiceHelper.h"

//start end is lowest and highest, e.g. d20 would be min = 1 max = 20
bool DiceHelper::dice(int dc, int start, int end, int mod) {
	default_random_engine randomEngine(time(0));
	uniform_int_distribution<int> roll(start, end);
	return roll(randomEngine)+mod > dc ? true : false;
}

int DiceHelper::dice(int start, int end, int mod) {
	default_random_engine randomEngine(time(0));
	uniform_int_distribution<int> roll(start, end);
	return roll(randomEngine)+mod;
}