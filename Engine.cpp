#include "Engine.h"

Engine::Engine()
{	
	hwnd = NULL;
	currentLevel = new Level();
}

Engine::~Engine()
{

}

bool Engine::Init(HWND* _hwnd, Config* _config)
{
	hwnd = _hwnd;	
	config = _config;

	render = new Render();

	if(!render->Init(hwnd)) return false;

	QueryPerformanceFrequency(&ticksPerSecond);

	return true;
};

bool Engine::Recalc(double _timePassed)
{
	//Player
	currentLevel->player->MoveObject(_timePassed);

	//Camera
	if (currentLevel->camera->followPlayer)
	{
		currentLevel->camera->x = currentLevel->player->x;
		currentLevel->camera->y = currentLevel->player->y;

		currentLevel->player->scrX = currentLevel->player->x + (currentLevel->camera->x - currentLevel->camera->width / 2);
		currentLevel->player->scrY = currentLevel->player->y + (currentLevel->camera->y - currentLevel->camera->height / 2);
	}
	else
	{
		currentLevel->player->scrX = currentLevel->player->x + (currentLevel->camera->x - currentLevel->camera->width / 2);
		currentLevel->player->scrY = currentLevel->player->y + (currentLevel->camera->y - currentLevel->camera->height / 2);
	}

	//Blocks
	for (vecIt = 0; vecIt != currentLevel->blocks.size(); vecIt++)
	{
		block = currentLevel->blocks.at(vecIt);

		block->scrX = block->x + (currentLevel->camera->x - currentLevel->camera->width / 2);
		block->scrY = block->y + (currentLevel->camera->y - currentLevel->camera->height / 2);
	}

	return true;
};

bool Engine::Redraw(double _timePassed)
{
	render->Redraw(*currentLevel, _timePassed);

	return true;
};

bool Engine::LoadLevel()
{
	//TODO: Level loading from storage

	return true;
}

bool Engine::LoadMainScreen()
{
	//Player
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

	//Blocks
	currentLevel->AddBlock(20, 200, 50, 200);
	currentLevel->AddBlock(400, 20, 200, 50);

	//Camera
	currentLevel->camera = new Camera();

	currentLevel->camera->followPlayer = true;

	currentLevel->camera->width = config->RES_X;
	currentLevel->camera->height = config->RES_Y;

	//currentLevel->camera->x = config->RES_X / 2;
	//currentLevel->camera->y = config->RES_Y / 2;


	return true;
}