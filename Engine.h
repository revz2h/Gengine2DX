#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include <Windows.h>
#include "Render.h"
#include "Level.h"

class Engine
{	
	HWND hwnd;
	Render render;	

public:	
	Level* currentLevel;
	LARGE_INTEGER ticksPerSecond;

	Engine();
	~Engine();

	bool Init(HWND &_hwnd);
	bool LoadLevel();

	bool LoadMainScreen();

	bool Recalc(double &_timePassed);
	bool Redraw(double &_timePassed);

};
#endif