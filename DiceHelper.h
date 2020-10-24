#pragma once
// Main dice roller for DND style mechanics
// Should only return values
// Functions for rolling a d20, d5 and other dice needed for game mechanics. 

#include <random>
#include <ctime>


using namespace std;

class DiceHelper
{
public:
	bool dice(int dc, int min, int max, int mod);
	int dice(int min, int max, int mod);
};

