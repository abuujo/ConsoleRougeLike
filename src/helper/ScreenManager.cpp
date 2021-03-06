#include "ScreenManager.h"


// Constructor and Desctructor functions for init

ScreenManager::ScreenManager() {
	screen.setWindow(100, 40);
	clearVector();
}

ScreenManager::~ScreenManager() {
	clearVector();
}

//Display the main menu.
int ScreenManager::buildMenu() {
	int chosen = 3;
	system("CLS");
	screen.outputText(20,5,11,"New Town - test rougelike :D");
	screen.outputText(20, 6, 11, "Move up W move down S enter to select");
	char c = '0';

	int selected = 1;
	while(c != char(13)){
		// Menu
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		screen.gotoxy(20, 7 + selected);
		cout << "->";

		screen.gotoxy(23, 8);
		cout << "Start";
		screen.gotoxy(23, 9);
		cout << "Options";
		screen.gotoxy(23, 10);
		cout << "Quit";


		screen.gotoxy(100, 40);
		c = _getch();

		if (c == 's') {
			selected += 1;
			screen.gotoxy(20, 7 + selected-1);
			cout << "  ";
		}
		else if (c == 'w') {
			selected -= 1;
			screen.gotoxy(20, 7 + selected + 1);
			cout << "  ";
		}
		if (selected < 1) {
			selected = 1;
		}
		else if (selected > 3) {
			selected = 3;
		}


		this_thread::sleep_for(100ms);
	}
	system("CLS");
	return selected;
}

//Display Options Menu
void ScreenManager::buildOptions() {
	
}

// Load map and border chars into vectors.
void ScreenManager::buildMap(char level) {
	string levelFile = to_string(level - '0') + ".txt"; // not universal
	inputData("border.txt", &_borderlData); // Border
	inputData(levelFile, &_levelData); // Level

	// Find and init Entities.
	int tileNo = 0;
	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			char tile = _levelData[i][j];
			switch (tile) {
			case '8':
				_player.init(1,20,13,3,16,0,0,15);
				_player.setPosition(j,i);
				break;
			case '7':
				_NPCS.push_back(Npc(10, 10, 3, 12, j, i));
			}
			tileNo++;
		}
	}
}

// Load legend chars into vector
void ScreenManager::buildLegend() {
	inputData("legend.txt", &_legendData); // Level
}

// Add screen Data together
void ScreenManager::displayGame(char level) {
	buildMap(level);
	buildLegend();

	printVector(2, 3, _borderlData, false);
	printVector(5, 5, _levelData, true);
	printVector(70, 5, _legendData, false);

	screen.outputText(78, 18, 15, "Legend");
	screen.outputText(73, 20, 10, "T");
	screen.outputText(75, 20, 15, "tree");
	screen.outputText(73, 21, 12, ".");
	screen.outputText(75, 21, 15, "floor");
	screen.outputText(73, 22, 14, "#");
	screen.outputText(75, 22, 14, "wall");
	screen.outputText(82, 20, 11, "G");
	screen.outputText(84, 20, 15, "goblin");
	screen.outputText(82, 21, 13, "@");
	screen.outputText(84, 21, 15, "player");
}

void ScreenManager::updateScreen(int dx, int dy) {

	int x = 0;
	int y = 0;
	_player.getPosition(x,y);
	 
	int newX = x + dx;
	int newY = y + dy;

	char newTile = _levelData[newY][newX];

	switch (newTile) {
	case '0': // '.'
		_player.setPosition(newX, newY);
		_levelData[newY][newX] = '8';
		_levelData[y][x] = newTile;
		break;
	case '1': // '#'
		addMessage("You ran into a wall...");
		break;
	case '2': // '#'
		break;
	case '3': // '+'
		break;
	case '4': // '/'
		break;
	case '5': // 'T'
		addMessage("You ran into a tree...");
		break;
	case '7': // 'G'
		int enemyIndex = 0;
		bool complete = false;
		for (int i = 0; i < _NPCS.size(); i++) {
			int npcX;
			int npcY;
			_NPCS[i].getPosition(npcX, npcY);
			if (npcX == newX && npcY == newY) {
				enemyIndex = i;
				break;
			}
		}

		if (combatManager(&_NPCS[enemyIndex])) {
			// Above function returned true : Enemy died
			_NPCS.erase(_NPCS.begin() + enemyIndex);
			_levelData[newY][newX] = '0';
			if (_NPCS.size() == 0) {
				addMessage("You have defeated all the enemies");
			}
		}

		if (_player.getHealth() <= 0) {
			gui.endGameScreen();
		}

		break;
	}

	screen.outputText(76, 7, 15, "Player Stats");
	screen.outputText(74, 9, 15, "                ");
	screen.outputText(74, 9, 15, "Health :  ");

	int healthColour = (_player.getHealth() > 10) ? 10 : 12;
	screen.outputText(83, 9, healthColour, to_string(_player.getHealth()));

	printMessage();
	printVector(5, 5, _levelData, true);

}

void ScreenManager::addMessage(string message) {
	if (_gameMessages.size() > 5) {
		_gameMessages.erase(_gameMessages.begin());
	}
	_gameMessages.push_back(message);
}

void ScreenManager::printMessage() {
	screen.gotoxy(3, 30);
	for (int i = 0; i < 6; i++) {
		screen.outputText(3, 30 + i, 15, "                                             ");
	}
	for (int i = 0; i < 6; i++) {
		if (i < _gameMessages.size()) {
			screen.outputText(3, 30 + i, 14 , _gameMessages[i]);
		}
	}
}

void ScreenManager::randomMonsterMovement() {

	for (int i = 0; i < _NPCS.size(); i++) {
		int x;
		int y;
		_NPCS[i].getPosition(x, y);

		_NPCS[i].setPosition(x + 1, y + 1);

		_levelData[y][x] = '0';
		_levelData[y + 1][x + 1] = '7';

	}
}

// Private Functions : To be used only by ScreenManager Class

// Load data from an input path into a string vector
void ScreenManager::inputData(string filePath, vector <string>* _vector) {
	ifstream file;
	file.open(filePath);
	if (file.fail()) {
		perror(filePath.c_str());
		system("PAUSE");
		exit(1);
	}
	string line;
	while (getline(file, line)) {
		_vector->push_back(line);
	}
	file.close();
}

// Clear every vector used in ScreenManager
void ScreenManager::clearVector() {
	_levelData.clear();
	_legendData.clear();
	_borderlData.clear();
	_gameMessages.clear();
}

// Print the data from passed vector
void ScreenManager::printVector(int startx, int starty, vector <string> _vector, bool vision) {

	int tileIndex = 0;
	for (int y = 0; y < _vector.size(); y++) {
		for (int x = 0; x < _vector[y].length(); x++) {
			screen.outputChar(15, startx + x, starty + y, ' ');

			/*
			bool inVision = isInRange(x,y);
			if (vision == true && inVision == false) {
				
				continue;
			
			}
			*/
			// Get attribute
			int type = _vector[y][x] - '0';
			screen.outputChar(tiles[type].colour, startx + x, starty + y, tiles[type].tile);

			tileIndex++;
		}
	}
}

// Player attacks Goblin, who attacks back (bool return if enemy is dead)
bool ScreenManager::combatManager(Npc* enemy) {
	// Attack the Goblin
	if (rd.dice(enemy->getArmorClass(), 0, 20, _player.getWeaponMod())) {
		int damage = rd.dice(1, 8, 3); // roll 1d8 + 3
		enemy->setHealth(-1 * damage);
		string message = "You attack the monster for " + to_string(damage) + " damage.";
		addMessage(message);

		//Check if Goblin is dead
		if (enemy->getHealth() <= 0) {
			addMessage("You defeat the Goblin.");
			return true;
		}
	}
	else {
		addMessage("You missed the Goblin.");
	}

	// Goblin attacks back
	if (rd.dice(_player.getArmorClass(), 0, 20, 0)) {
		int damage = rd.dice(1, 5, 1); // roll 1d5 + 1
		_player.setHealth(-1 * damage);
		string message = "The goblin hits you for " + to_string(damage) + " damage.";
		addMessage(message);
	}
	else  {
		addMessage("The goblin misses you.");
	}
	return false;
}

// Check fov range of Tile
bool ScreenManager::isInRange(int tileX, int tileY) {
	int playerX;
	int playerY;
	int playerVision = _player.getVision();
	_player.getPosition(playerX, playerY);

	int normX = tileX - playerX;
	int normY = tileY - playerY;
	int mag = magnitude(normX, normY);

	if (mag <= playerVision) {
		return fov(tileX, tileY, playerX, playerY);
	}
	return false;
}

// return SQRT(x^2+y^2)
int ScreenManager::magnitude(int x, int y) {
	return sqrt(pow(x, 2) + pow(y, 2));
}

// This function returns a line with all the _levelData tiles 
// that match the line algorithm. 
bool ScreenManager::fov(int tileX, int tileY, int pX, int pY) {

	// Draw a line from the player and check all the tiles that exist in that line
	line_algorithm(pX, pY, tileX, tileY, &_lineData);
	bool returnVal = true;
	string message;

	// sift through linedata to determine if the player has vision on the tile.
	int count = 0;
	for (int i = 0; i < _lineData.size() - 1;  i+= 2) {
		int x = _lineData[i];
		int y = _lineData[i+1];

		if ((_levelData[y][x] ) == '1' && i != _lineData.size()-1) {
			count++;
		}
	}

	if (count > 1) {
		returnVal = false;
		
	}
	else if (count == 1 && (_levelData[tileY][tileX] == '1')) {
		returnVal = true;
	}
	else if (count == 1) {
		returnVal = false;
	}

	_lineData.clear();
	return returnVal;
}

// Basic distance algorithm.
float distance2d(int x1, int y1, int x2, int y2) {
	float dx = (float)x1 - (float)x2;
	float dy = (float)y1 - (float)y2;
	return sqrt((dx * dx) + (dy * dy));
}

// shoutout to rltk
void ScreenManager::line_algorithm(int x1, int y1, int x2, int y2, vector <int>* _lineData) {
	float x = static_cast<float>(x1) + 0.5F;
	float y = static_cast<float>(y1) + 0.5F;

	float dest_x = static_cast<float>(x2);
	float dest_y = static_cast<float>(y2);

	float n_steps = distance2d(x1, y1, x2, y2);
	int steps = static_cast<const int>(std::floor(n_steps) + 1);

	float slope_x = (dest_x - x) / n_steps;
	float slope_y = (dest_y - y) / n_steps;

	for (int i = 0; i < steps; ++i) {

		// Create a string structure with xychar
		//[0] -> x [1] -> y [2] -> char (tile index)
		
		_lineData->push_back(x);
		_lineData->push_back(y);
		x += slope_x;
		y += slope_y;
	}

}