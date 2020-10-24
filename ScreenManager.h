#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <vector>
#include <sstream>
#include <thread>

#include "Player.h"
#include "Npc.h"
#include "DiceHelper.h"

using namespace std;

// We will assume the screen is 

class ScreenManager 
{
public:

	// Class const dest
	ScreenManager();
	~ScreenManager();

	// Screen Functions
	int buildMenu();
	void displayGame(char level);
	void buildMap(char level);
	void buildLegend();
	void buildOptions();
	void updateScreen(int dx, int dy);
	void printMessage();
	void randomMonsterMovement();
	void exitGameScreen();

private:
	void setWindow(int Width, int Height);
	void gotoxy(int x, int y);
	void clearVector();
	void outputChar(int attribute, int x, int y, char c);
	void addMessage(string message);
	void outputText(int x, int y, int attribute, string message);
	void inputData(string filePath, vector <string> *_vector);
	void printVector(int startx, int starty, vector <string> _vector);
	bool combatManager(Npc* enemy);
	void endGameScreen();

	// Variables
	vector <string> _levelData;
	vector <string> _legendData;
	vector <string> _borderlData;
	vector <string> _gameMessages;


	vector <Npc> _NPCS;
	HANDLE Handle;

	Player _player;
	DiceHelper rd;

	// Tile Indexer
	struct TILE_INDEX {
		char tile;
		int colour;
		bool interactable;
	};

	// Tiles
	TILE_INDEX tiles[9] = {
		{ '.', 8,  true },			// (0) TILE_ROCKFLOOR
		{ '#', 14,  false },		// (1) TILE_WALL
		{ '+', 14,  false },		// (2) TILE_CLOSEDDOOR
		{ '/', 11,  true },			// (3) TILE_OPENDOOR
		{ ',', 10, true },			// (4) TILE_GRASS
		{ 'T', 10, false },			// (5) TILE_TREE
		{ ' ', 10, false },			// (6) TILE_TREE
		{ 'G', 11, false },			// (7) TILE_TREE
		{ '@', 12, false },			// (8) TILE_TREE
	};

};

