#include <windows.h>
#include "defs.h"
#include "util.h"
#include "Engine.h"

Config config;
Engine engine;

bool LoadConfig(Config &_config)
{
	_config.GAME_BUILD[0] = 0;
	_config.GAME_BUILD[1] = 1;
	_config.GAME_BUILD[2] = 2;

	snprintf(&_config.GAME_VERSION[0], sizeof(_config.GAME_VERSION), STRFMT_VERSION, _config.GAME_BUILD[0], _config.GAME_BUILD[1], _config.GAME_BUILD[2]);

	snprintf(&_config.GAME_TITLE[0], sizeof(_config.GAME_TITLE), STRFMT_GAME_TITLE, _config.GAME_VERSION);

	_config.RES_X = 1024;
	_config.RES_Y = 768;

	return true;
}

LRESULT CALLBACK WinProc(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			
		case WM_KEYDOWN:
			switch (_wParam)
			{
				//TODO: Mapable controls
				case 'W':
					engine.currentLevel->player->accelVec[1] = *engine.currentLevel->player->maxAccel;
					break;
				case 'S': 
					engine.currentLevel->player->accelVec[1] = *engine.currentLevel->player->maxAccel * -1;
					break;
				case 'A':
					engine.currentLevel->player->accelVec[0] = *engine.currentLevel->player->maxAccel * -1;
					break;
				case 'D':
					engine.currentLevel->player->accelVec[0] = *engine.currentLevel->player->maxAccel;
					break;
				default:
					break;
			}

			break;
		case WM_KEYUP:
			switch (_wParam)
			{
				//TODO: Mapable controls
				case 'W':
					engine.currentLevel->player->accelVec[1] = 0;
					break;
				case 'S':
					engine.currentLevel->player->accelVec[1] = 0;
					break;
				case 'A':
					engine.currentLevel->player->accelVec[0] = 0;
					break;
				case 'D':
					engine.currentLevel->player->accelVec[0] = 0;
					break;
			}
			break;
	}
	return DefWindowProc(_hwnd, _uMsg, _wParam, _lParam);
}

bool ConstructWindow(HWND &_hwnd, HINSTANCE &_hInstance)
{
	WNDCLASSEX winClass;

	ZeroMemory(&winClass, sizeof(winClass));

	winClass.cbSize = sizeof(winClass);
	winClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	winClass.hInstance = _hInstance;
	winClass.lpfnWndProc = WinProc;
	winClass.lpszClassName = "GengineDX";

	winClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&winClass);

	_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "GengineDX", config.GAME_TITLE, WS_OVERLAPPED, 0, 0, config.RES_X, config.RES_Y, NULL, NULL, _hInstance, NULL);

	if (!_hwnd) return false;
	else return true;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	HWND hwnd;
	MSG message;

	double timerStart = 0, timerPass = 1;

	if(!LoadConfig(config)) return -1;

	if(!ConstructWindow(hwnd, hInstance))  return -1;	

	ShowWindow(hwnd, nCmdShow);

	if (!engine.Init(hwnd)) return -1;

	if (!engine.LoadMainScreen()) return -1;

	message.message = WM_NULL;

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, hwnd, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}
		else
		{
			timerStart = GetTickCount();

			engine.Recalc(timerPass);

			engine.Redraw(timerPass);

			timerPass =  (GetTickCount() - timerStart) / engine.ticksPerSecond.QuadPart * 10000;
		}
	}

	return 0;
}