#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include <Windows.h>
#include "Render.h"
#include "Level.h"

struct Config
{
	int GAME_BUILD[2]; //0 - Major, 1 - Minor, 2 - Build
	int RES_X, RES_Y;

	char GAME_VERSION[32];
	char GAME_TITLE[256];
};

class Engine
{	
	HWND* hwnd;
	Render* render;
	int vecIt;
	Block *block;

public:	
	Level* currentLevel;
	Config* config;

	LARGE_INTEGER ticksPerSecond;	

	Engine();
	~Engine();

	bool Init(HWND* _hwnd, Config* _config);
	bool LoadLevel();

	bool LoadMainScreen();

	bool Recalc(double _timePassed);
	bool Redraw(double _timePassed);

};
#endif