#include "ScreenManager.h"

// Constructor and Desctructor functions for init

ScreenManager::ScreenManager() {
	setWindow(100, 40);
	clearVector();

}

ScreenManager::~ScreenManager() {
	clearVector();
}

// Exit game screen 
void ScreenManager::exitGameScreen() {

	// output endgame screen
	outputText(40, 13, 15, "                       ");
	outputText(40, 14, 12, "      Exit Game?       ");
	outputText(40, 15, 12, "    y = yes  n = no    ");
	outputText(40, 16, 15, "                       ");

	// wait for enter key
	char c = _getch();
	switch (c) {
	case 'y':
		system("CLS");
		exit(1);
	case 'n':
		updateScreen(0, 0);
		break;
	default:
		endGameScreen();
	}
}
//Display the main menu.
int ScreenManager::buildMenu() {
	int chosen = 3;
	system("CLS");
	outputText(20,5,11,"New Town - test rougelike :D");
	outputText(20, 6, 11, "Move up W move down S enter to select");
	char c = '0';

	int selected = 1;
	while(c != char(13)){
		// Menu
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		gotoxy(20, 7 + selected);
		cout << "->";

		gotoxy(23, 8);
		cout << "Start";
		gotoxy(23, 9);
		cout << "Options";
		gotoxy(23, 10);
		cout << "Quit";


		gotoxy(100, 40);
		c = _getch();

		if (c == 's') {
			selected += 1;
			gotoxy(20, 7 + selected-1);
			cout << "  ";
		}
		else if (c == 'w') {
			selected -= 1;
			gotoxy(20, 7 + selected + 1);
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
	string levelFile = to_string(level - '0') + ".txt";
	inputData("border.txt", &_borderlData); // Border
	inputData(levelFile, &_levelData); // Level

	// Find and init Entities.
	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			char tile = _levelData[i][j];
			switch (tile) {
			case '8':
				_player.init(1,20,13,3,16,0,0);
				_player.setPosition(j,i);
				break;
			case '7':
				_NPCS.push_back(Npc(10, 10, 3, 12, j, i));
			}
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

	printVector(2, 3, _borderlData);
	printVector(5, 5, _levelData);
	printVector(70, 5, _legendData);

	outputText(78, 18, 15, "Legend");
	outputText(73, 20, 10, "T"); 
	outputText(75, 20, 15, "tree");
	outputText(73, 21, 12, ".");
	outputText(75, 21, 15, "floor");
	outputText(73, 22, 14, "#");
	outputText(75, 22, 14, "wall");
	outputText(82, 20, 11, "G");
	outputText(84, 20, 15, "goblin");
	outputText(82, 21, 13, "@");
	outputText(84, 21, 15, "player");
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
			endGameScreen();
		}

		break;
	}

	outputText(76, 7, 15, "Player Stats");
	outputText(74, 9, 15, "                ");
	outputText(74, 9, 15, "Health : ");

	int healthColour = (_player.getHealth() > 10) ? 10 : 12;
	outputText(82, 9, healthColour, to_string(_player.getHealth()));

	printMessage();
	printVector(5, 5, _levelData);

}

void ScreenManager::addMessage(string message) {
	if (_gameMessages.size() > 3) {
		_gameMessages.erase(_gameMessages.begin());
	}
	_gameMessages.push_back(message);
}

void ScreenManager::printMessage() {
	gotoxy(3, 30);
	for (int i = 0; i < 4; i++) {
		outputText(3, 30 + i, 15, "                                             ");
	}
	for (int i = 0; i < 4; i++) {
		if (i < _gameMessages.size()) {
			outputText(3, 30 + i, 14 , _gameMessages[i]);
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

// Use cout to output message at x, y co-ords with attribute
void ScreenManager::outputText(int x, int y, int attribute, string message) {
	gotoxy(x, y);
	SetConsoleTextAttribute(Handle, attribute);
	cout << message;
}

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
void ScreenManager::printVector(int startx, int starty, vector <string> _vector) {
	for (int y = 0; y < _vector.size(); y++) {
		for (int x = 0; x < _vector[y].length(); x++) {
			// Get attribute
			int type = _vector[y][x] - '0';
			outputChar(tiles[type].colour, startx + x, starty + y, tiles[type].tile);
		}
	}
}

// Use cout to output char at x, y co-ords with attribute
void ScreenManager::outputChar(int attribute, int x, int y, char c) {
	gotoxy(x, y);
	SetConsoleTextAttribute(Handle, attribute);
	cout << c;
}

// Move to co-ords on the console screen
void ScreenManager::gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Establish the console window properties
void ScreenManager::setWindow(int Width, int Height) {
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(Handle, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility (get rid of _)
	SetConsoleCursorInfo(Handle, &cursorInfo);
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

// End game screen 
void ScreenManager::endGameScreen() {

	// output endgame screen
	outputText(40, 13, 15, "                       ");
	outputText(40, 14, 12, "     YOU HAVE DIED     ");
	outputText(40, 15, 12, "     Press enter..     ");
	outputText(40, 16, 15, "                       ");

	// wait for enter key
	while (_getch() != char(13)) {
		continue;
	}
	system("CLS");
	exit(1);
}

