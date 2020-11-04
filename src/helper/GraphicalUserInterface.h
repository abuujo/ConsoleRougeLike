#pragma once

// Includes
#include <conio.h>
#include "Screen.h"

class GraphicalUserInterface
{
public:
	void endGameScreen();
	bool exitGameScreen();
	bool characterMenu();

private:
	Screen screen;
};

// Helper class for building the GUI options
// Should include:
// > Shop
// > Spell list
// > Menu items and end / exit game screens
// > etc.
