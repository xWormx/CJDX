#include "CJwin.h"

WindowSize getClientRectSize(HWND hwnd)
{
	WindowSize winSize = {};
	RECT rect = {};

	GetClientRect(hwnd, &rect);

	winSize.width = (rect.right - rect.left);
	winSize.height = (rect.bottom - rect.top);

	return winSize;
}

float getCursorPosX_f(HWND hwnd)
{
	float result;

	if(GetCursorPos(&win32_states.cursor))
	{
		ScreenToClient(hwnd, &win32_states.cursor);

		WindowSize screenCoords = getClientRectSize(hwnd);
		result =  (float)win32_states.cursor.x/(screenCoords.width/2) - 1.0f;
	}

	return result;
}

float getCursorPosY_f(HWND hwnd)
{
	float result;

	if(GetCursorPos(&win32_states.cursor))
	{
		ScreenToClient(hwnd, &win32_states.cursor);

		WindowSize screenCoords = getClientRectSize(hwnd);
		result = -(float)win32_states.cursor.y/(screenCoords.height/2) + 1.0f;
	}

	return result;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM WParam, LPARAM LParam)
{
	LRESULT result = {};

	switch(message)
	{
			case WM_MOUSEMOVE:
			{

			} break;

			case WM_LBUTTONDOWN:
			{
				win32_states.leftKeyPressed = true;
			} break;

			case WM_LBUTTONUP:
			{
				win32_states.leftKeyPressed = false;
			} break;

			case WM_KEYDOWN:
			{
				checkKeyUp(WParam);
			} break;

			case WM_KEYUP:
			{
				checkKeyDown(WParam);
			} break;

			case WM_PAINT:
			{
				PAINTSTRUCT ps = {};
				HDC dc = BeginPaint(hwnd, &ps);

				WindowSize winSize = getClientRectSize(hwnd);
				
				EndPaint(hwnd, &ps);
			} break;

			case WM_DESTROY:
			{
					PostQuitMessage(1337);
					win32_states.running = false;
			} break;

			default:
			{
				result = DefWindowProc(hwnd, message, WParam, LParam);
			}
	}

	return result;
}

void checkKeyUp(WPARAM WParam)
{
	if(!win32_states.keyStates[WParam])
	{
		if(WParam == VK_UP)
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == VK_DOWN)
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == VK_LEFT)
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == VK_RIGHT)
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'A')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'B')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'C')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'D')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'E')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'F')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'G')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'H')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'I')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'J')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'K')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'L')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'M')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'N')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'O')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'P')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'Q')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'R')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'S')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'T')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'U')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'V')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'W')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'X')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'Y')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'Z')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'Å')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'Ä')
		{
				win32_states.keyStates[WParam] = true;
		}		
		if(WParam == 'Ö')
		{
				win32_states.keyStates[WParam] = true;
		}		
	}
}
void checkKeyDown(WPARAM WParam)
{
	if(WParam == VK_UP)
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == VK_DOWN)
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == VK_LEFT)
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == VK_RIGHT)
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'A')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'B')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'C')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'D')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'E')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'F')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'G')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'H')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'I')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'J')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'K')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'L')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'M')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'N')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'O')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'P')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'Q')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'R')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'S')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'T')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'U')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'V')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'W')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'X')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'Y')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'Z')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'Å')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'Ä')
	{
			win32_states.keyStates[WParam] = false;
	}		
	if(WParam == 'Ö')
	{
			win32_states.keyStates[WParam] = false;
	}		
 }
