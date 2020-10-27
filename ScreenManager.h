#pragma once
#include <fstream>
#include <conio.h>
#include <vector>
#include <sstream>
#include <thread>
#include <math.h>

#include "Player.h"
#include "Npc.h"
#include "DiceHelper.h"
#include "Screen.h"
#include "GraphicalUserInterface.h"

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
	void clearVector();
	void addMessage(string message);
	void inputData(string filePath, vector <string> *_vector);
	void printVector(int startx, int starty, vector <string> _vector, bool vision);
	bool combatManager(Npc* enemy);
	void endGameScreen();
	bool isInRange(int tileX, int tileY);
	int magnitude(int x, int y);
	bool fov(int x1, int y1, int x2, int y2);
	bool line(int x1, int y1, int x2, int y2);

	// Variables
	vector <string> _levelData;
	vector <string> _legendData;
	vector <string> _borderlData;
	vector <string> _gameMessages;


	vector <Npc> _NPCS;
	Screen screen;
	GraphicalUserInterface gui;

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

