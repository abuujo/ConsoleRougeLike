#include "GraphicalUserInterface.h"

// End game screen as overlay
void GraphicalUserInterface::endGameScreen() {

	// output endgame screen
	screen.outputText(40, 13, 15, "                       ");
	screen.outputText(40, 14, 12, "     YOU HAVE DIED     ");
	screen.outputText(40, 15, 12, "     Press enter..     ");
	screen.outputText(40, 16, 15, "                       ");

	// wait for enter key
	while (_getch() != char(13)) {
		continue;
	}
	system("CLS");
	exit(1);
}

// Exit game screen as overlay
bool GraphicalUserInterface::exitGameScreen() {

	// output endgame screen
	screen.outputText(40, 13, 15, "                       ");
	screen.outputText(40, 14, 12, "      Exit Game?       ");
	screen.outputText(40, 15, 12, "    y = yes  n = no    ");
	screen.outputText(40, 16, 15, "                       ");

	// wait for enter key
	char c = _getch();
	switch (c) {
	case 'y':
		return true;
	case 'n':
		return false;
	default:
		exitGameScreen();
	}
}

// Ingame character menu
bool GraphicalUserInterface::characterMenu() {
	int selected = 1;
	char c = '0';

	screen.outputText(7, 7, 15,     "  Menu                      ");
	screen.outputText(7, 8, 15,     "                            ");

	while (c != char(13)) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		
		screen.outputText(7, 9, 15, "   *Spells                    ");
		screen.outputText(7, 10, 15,"                           ");
		screen.outputText(7, 11, 15,"   *Items                     ");
		screen.outputText(7, 12, 15,"                           ");
		screen.outputText(7, 13, 15,"   *Armour                    ");
		screen.outputText(7, 14, 15,"                           ");
		screen.outputText(7, 15, 15,"   *Weapons                   ");
		screen.outputText(7, 16, 15,"                           ");
		screen.gotoxy(7, 8 + selected);
		cout << "->";
		c = _getch();

		if (c == 's') {
			selected += 2;
			screen.gotoxy(7, 8 + selected - 2);
			cout << "  ";
		}
		else if (c == 'w') {
			selected -= 2;
			screen.gotoxy(7, 8 + selected + 2);
			cout << "  ";
		}
		if (selected < 1) {
			selected = 1;
		}
		else if (selected > 7) {
			selected = 7;
		}
	}
	return false;
}

