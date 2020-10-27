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
	ScreenManager screenManager;
	GraphicalUserInterface gui;
	
};

