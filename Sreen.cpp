#include "Screen.h"

// Establish the console window properties
void Screen::setWindow(int Width, int Height) {
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

// Use cout to output message at x, y co-ords with attribute
void Screen::outputText(int x, int y, int attribute, string message) {
	gotoxy(x, y);
	SetConsoleTextAttribute(Handle, attribute);
	cout << message;
}

// Use cout to output char at x, y co-ords with attribute
void Screen::outputChar(int attribute, int x, int y, char c) {
	gotoxy(x, y);
	SetConsoleTextAttribute(Handle, attribute);
	cout << c;
}

// Move to co-ords on the console screen
void Screen::gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}