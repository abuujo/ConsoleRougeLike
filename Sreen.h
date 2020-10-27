#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;

class Screen
{
public:
	// Window init
	void setWindow(int Width, int Height);

	// Display
	void gotoxy(int x, int y);
	void outputChar(int attribute, int x, int y, char c);
	void outputText(int x, int y, int attribute, string message);

private:
	HANDLE Handle;
};

