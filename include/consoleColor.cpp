#include "consoleColor.h"
#ifdef _WIN32
#include <windows.h>
#define FOREGROUND_REGULAR	15
void color(int c) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
}

#else
#define FOREGROUND_REGULAR	15
#define FOREGROUND_GREEN 0
#define FOREGROUND_BLUE 0
#define FOREGROUND_BLUE 0
void color(int c) {}
#endif