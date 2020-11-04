#pragma once

// Includes
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;

class Screen
{
public:
	void setWindow(int Width, int Height);
	void gotoxy(int x, int y);
	void outputChar(int attribute, int x, int y, char c);
	void outputText(int x, int y, int attribute, string message);

private:
	HANDLE Handle;
};

