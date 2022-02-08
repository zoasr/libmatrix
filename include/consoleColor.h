#pragma once
#ifdef _WIN32
#include <windows.h>
#define FOREGROUND_REGULAR	15
void color(int c);
#else
#define FOREGROUND_REGULAR	15
#define FOREGROUND_GREEN 0
#define FOREGROUND_BLUE 0
#define FOREGROUND_BLUE 0
void color(int c);
#endif
