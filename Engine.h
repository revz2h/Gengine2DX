#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include <Windows.h>
#include "Render.h"
#include "Level.h"

struct Config
{
	int GAME_BUILD[2]; //0 - Major, 1 - Minor, 2 - Build
	int RES_X, RES_Y, HITBOX_WIDTH;

	char GAME_VERSION[32];
	char GAME_TITLE[256];
};

class Engine
{	
	HWND* hwnd;
	Render* render;
	Block *block;
	int vecIt;

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

	bool InAxisRange(double _value, double _min, double _max);

	bool RectCollision(DynamicObject* _firstObject, BaseObject* _secondObject);

	bool DetectCollision(DynamicObject* _object);

	void MoveObject(double _timePassed, DynamicObject* _dynamicObject);
};
#endif