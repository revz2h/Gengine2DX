#include "Engine.h"

Engine::Engine()
{	
	hwnd = NULL;
	currentLevel = new Level();
}

Engine::~Engine()
{

}

bool Engine::Init(HWND &_hwnd)
{
	hwnd = _hwnd;	

	if(!render.Init(hwnd)) return false;

	QueryPerformanceFrequency(&ticksPerSecond);

	return true;
};

bool Engine::Recalc(double &_timePassed)
{

#pragma region Player
	currentLevel->player->MoveObject(_timePassed);
#pragma endregion

	return true;
};

bool Engine::Redraw(double &_timePassed)
{
	render.Redraw(*currentLevel, _timePassed);

	return true;
};

bool Engine::LoadLevel()
{
	//TODO: Level loading from storage

	return true;
}

bool Engine::LoadMainScreen()
{
	currentLevel->showFps = true;
	currentLevel->devMode = true;

	currentLevel->player->maxAccel[0] = 60.0f;	
	currentLevel->player->maxAccel[1] = 60.0f;

	currentLevel->player->maxDeccel[0] = 80.0f;
	currentLevel->player->maxDeccel[1] = 80.0f;

	currentLevel->player->maxSpeed[0] = 50.0f;
	currentLevel->player->maxSpeed[1] = 50.0f;

	currentLevel->player->width = 50.0f;
	currentLevel->player->height = 50.0f;

	currentLevel->player->x = 20.0f;
	currentLevel->player->y = 20.0f;

	currentLevel->player->drawHitbox = true;
	
	return true;
}