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