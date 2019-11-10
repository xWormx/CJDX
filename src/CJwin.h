#define SCREEN_WIDTH 960.0f
#define SCREEN_HEIGHT 720.0f 

#define WIN32_LEAN_AND_MEAN

#include <dwmapi.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

struct WindowSize
{
	int width = 0;
	int height = 0;
};

struct windows_States
{
	int keyStates[256] = {0};
	bool running = true;

	bool leftKeyPressed = false;
	POINT cursor = {};

};

windows_States win32_states = {};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

WindowSize getClientRectSize(HWND hwnd);

void checkKeyUp(WPARAM WParam);
void checkKeyDown(WPARAM WParam);

float getCursorPosX_f();
float getCursorPosY_f();

