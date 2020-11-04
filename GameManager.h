#pragma once

#include "ScreenManager.h"
#include "GraphicalUserInterface.h"

using namespace std;

// Main manager for running the game states
class GameManager
{
public:
	GameManager();
	void startGame();

private:

	// Screen States
	int menu();
	void options();
	void runGame();

	// Settings
	char _settings[6];
	void loadSettings();
	void changeSettings();

	// Variables
	vector <string> _screenMatrix;
	Screen screen;
	ScreenManager screenManager;
	GraphicalUserInterface gui;

	// Tile Indexer
	struct TILE_INDEX {
		string name;
		int maxDMGROll; // roll 1dmaxDMGRoll
		int noRolls;
		int saveDC;
		bool halfOnSuccess;
		int spellLevel;
		bool aoe;
		int radius;
		int range;
	};

	// Tiles
	TILE_INDEX tiles[10] = {
		{ "Firebolt", 8, 1, 15 , true, 0, false, 0, 7},
	};

	
};

