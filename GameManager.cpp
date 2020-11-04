#include "GameManager.h"

GameManager::GameManager() {
}

void GameManager::startGame() {
	int result = menu();
	switch (result) {
		case 1: // Run the Game
			runGame();
			break;
		case 2: // Alter Options
			options();
			break;
		case 3: // Exit Game
			if (gui.exitGameScreen() == false) {
				startGame();
			}
			else {
				system("CLS");
				exit(1);
			}
		default:// Return to menu
			startGame();
	}
}
 
// Give user access to options / game start.
int GameManager::menu() {
	//Return 1 for start game, 2 for options and 3 for quit
	return screenManager.buildMenu();
}

// Alter Options
void GameManager::options() {
	loadSettings();
	screenManager.buildOptions();
	// Place Settings at relevant points

}

// Load Level and characters, start game.
void GameManager::runGame() {
	// Load Settings
	loadSettings();

	// Load Level
	screenManager.displayGame(_settings[5]);

	// Main game loop
	int count = 0;
	while (1) {
		// This loop will wait before doing anything.
		this_thread::sleep_for(10ms); 
		count++;
		if(count == 10){
			count = 0;

			// Random Goblin Movement
			//screenManager.randomMonsterMovement();
		}

		char input;
		input = _getch();
		switch (input) {
		case 'h' :
			if (gui.characterMenu() == false) {
				screenManager.updateScreen(0, 0);
			}
			break;
		case 'w':
		case 'W': // Move Up
			screenManager.updateScreen(0,-1);
			break;
		case 's':
		case 'S': // Move Down
			screenManager.updateScreen(0,1);
			break;
		case 'a':
		case 'A': // Move Left
			screenManager.updateScreen(-1, 0);
			break;
		case 'd':
		case 'D': // Move Right
			screenManager.updateScreen(1, 0);
			break;
		case 'q':
		case 'Q': // Quit Game Screen
			if (gui.exitGameScreen() == false) {
				screenManager.updateScreen(0, 0);
				break;
			}
			else {
				system("CLS");
				exit(1);
			}
			break;
		default:
			break;
		}

	}

}

// Load game settings from settings file
// 0 -> up, 1-> down, 2-> left, 3-> right, 4-> difficulty (int) 5-> level
void GameManager::loadSettings() {
	string filePath = "settings.txt";
	ifstream file;
	file.open(filePath);
	if (file.fail()) {
		perror(filePath.c_str());
		system("PAUSE");
		exit(1);
	}
	string line;
	getline(file, line);
	for(int i = 0 ; i < line.length() ; i++){
		_settings[i] = line[i];
	}
	file.close();
}