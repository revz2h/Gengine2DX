#include "Engine.h"

Engine::Engine()
{	
	hwnd = NULL;
	currentLevel = new Level();

	devMode = false;
}

Engine::~Engine()
{
}

bool Engine::InAxisRange(double _value, double _min, double _max)
{
	return (_value > _min) && (_value < _max);
}

bool Engine::RectCollision(DynamicObject* _firstObject, BaseObject* _secondObject)
{
	if (InAxisRange(_firstObject->x, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y, _secondObject->y, _secondObject->y2) ||
		InAxisRange(_firstObject->x2, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y, _secondObject->y, _secondObject->y2) ||
		InAxisRange(_firstObject->x, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y2, _secondObject->y, _secondObject->y2) ||
		InAxisRange(_firstObject->x2, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y2, _secondObject->y, _secondObject->y2)
	) return true;

	//TODO: Have detectable sides for more precice collision detection
	/*------------------------------------------------------------------------------------------------------------------
	//-- Doesn't work when you enter the object too far in next frame, and can't detect witch side you're impacting from
	//-------------------------------------------------------------------------------------------------------------------
	if (InAxisRange(_firstObject->x, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y - config->HITBOX_WIDTH, _secondObject->y, _secondObject->y2)
		||
		InAxisRange(_firstObject->x2, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y - config->HITBOX_WIDTH, _secondObject->y, _secondObject->y2))
	{
		_firstObject->collidingTop = true;
		_secondObject->collidingBottom = true;

		return true;
	}

	if (InAxisRange(_firstObject->x2 + config->HITBOX_WIDTH, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y, _secondObject->y, _secondObject->y2)
		||
		InAxisRange(_firstObject->x2 + config->HITBOX_WIDTH, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y2, _secondObject->y, _secondObject->y2))
	{
		_firstObject->collidingRight = true;
		_secondObject->collidingLeft = true;

		return true;
	}

	if (InAxisRange(_firstObject->x2, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y2 + config->HITBOX_WIDTH, _secondObject->y, _secondObject->y2)
		||
		InAxisRange(_firstObject->x, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y2 + config->HITBOX_WIDTH, _secondObject->y, _secondObject->y2))
	{
		_firstObject->collidingBottom = true;
		_secondObject->collidingTop = true;

		return true;
	}

	if (InAxisRange(_firstObject->x - config->HITBOX_WIDTH, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y, _secondObject->y, _secondObject->y2)
		||
		InAxisRange(_firstObject->x - config->HITBOX_WIDTH, _secondObject->x, _secondObject->x2) && InAxisRange(_firstObject->y2, _secondObject->y, _secondObject->y2))
	{
		_firstObject->collidingLeft = true;
		_secondObject->collidingRight = true;

		return true;
	}

	_firstObject->collidingLeft = false;
	_firstObject->collidingRight = false;
	_firstObject->collidingBottom = false;
	_firstObject->collidingTop = false;
	
	_secondObject->collidingTop = false;
	_secondObject->collidingRight = false;
	_secondObject->collidingLeft = false;
	_secondObject->collidingBottom = false;
	*/

	return false;
}

bool Engine::DetectCollision(DynamicObject* _object)
{
	if (!_object->collidable) return false;

	//Detect collision into blocks
	for (vecIt = 0; vecIt != currentLevel->blocks.size(); vecIt++)
	{
		block = currentLevel->blocks.at(vecIt);

		if (block->collidable)
		{
			if (RectCollision(_object, block))
			{
				_object->colliding = true;
				block->colliding = true;

				return true;
			}
			else
			{
				_object->colliding = false;
				block->colliding = false;
			};
		}
	}

	return false;
}

void Engine::MoveObject(double _timePassed, DynamicObject* _dynamicObject)
{
	int xTmp, yTmp;

	// X - axis
	if (_dynamicObject->accelVec[0]) //Accelarating
	{
		//Max speed check
		if (abs(_dynamicObject->speedVec[0]) < _dynamicObject->maxSpeed[0])
			_dynamicObject->speedVec[0] += _dynamicObject->accelVec[0] * _timePassed;
		else
		{
			if (_dynamicObject->speedVec[0] > 0) _dynamicObject->speedVec[0] = _dynamicObject->maxSpeed[0];
			else _dynamicObject->speedVec[0] = _dynamicObject->maxSpeed[0] * -1;
		}			

		xTmp = _dynamicObject->x;

		_dynamicObject->SetX(_dynamicObject->x + _dynamicObject->speedVec[0] * _timePassed);	

		if (DetectCollision(_dynamicObject))
		{
			_dynamicObject->SetX(xTmp);

			_dynamicObject->speedVec[0] *= 0.5;
			_dynamicObject->accelVec[0] *= 0.5;
		}		
	}
	else if (_dynamicObject->speedVec[0]) //Decelarating
	{
		if (_dynamicObject->speedVec[0] > 0)
		{
			_dynamicObject->speedVec[0] -= _dynamicObject->maxDeccel[0] * _timePassed;

			if (_dynamicObject->speedVec[0] < 0) _dynamicObject->speedVec[0] = 0;
		}
		else
		{
			_dynamicObject->speedVec[0] += _dynamicObject->maxDeccel[0] * _timePassed;

			if (_dynamicObject->speedVec[0] > 0) _dynamicObject->speedVec[0] = 0;
		}

		xTmp = _dynamicObject->x;

		_dynamicObject->SetX(_dynamicObject->x + _dynamicObject->speedVec[0] * _timePassed);

		if (DetectCollision(_dynamicObject))
		{
			_dynamicObject->SetX(xTmp);

			_dynamicObject->speedVec[1] *= 0.5;
		}
	}

	// Y - axis
	if (_dynamicObject->accelVec[1]) //Accelarating
	{
		//Max speed check
		if (abs(_dynamicObject->speedVec[1]) < _dynamicObject->maxSpeed[1])
			_dynamicObject->speedVec[1] += _dynamicObject->accelVec[1] * _timePassed;
		else
		{
			if (_dynamicObject->speedVec[1] > 0) _dynamicObject->speedVec[1] = _dynamicObject->maxSpeed[1];
			else _dynamicObject->speedVec[1] = _dynamicObject->maxSpeed[1] * - 1;
		}

		yTmp = _dynamicObject->y;

		_dynamicObject->SetY(_dynamicObject->y + _dynamicObject->speedVec[1] * _timePassed);

		if (DetectCollision(_dynamicObject))
		{		
			_dynamicObject->SetY(yTmp);
			
			_dynamicObject->speedVec[1] *= 0.5;
			_dynamicObject->accelVec[1] *= 0.5;
		}		
	}
	else if (_dynamicObject->speedVec[1]) //Decelarating
	{
		if (_dynamicObject->speedVec[1] > 0)
		{
			_dynamicObject->speedVec[1] -= _dynamicObject->maxDeccel[1] * _timePassed;

			if (_dynamicObject->speedVec[1] < 0) _dynamicObject->speedVec[1] = 0;
		}
		else
		{
			_dynamicObject->speedVec[1] += _dynamicObject->maxDeccel[1] * _timePassed;

			if (_dynamicObject->speedVec[1] > 0) _dynamicObject->speedVec[1] = 0;
		}

		yTmp = _dynamicObject->y;

		_dynamicObject->SetY(_dynamicObject->y + _dynamicObject->speedVec[1] * _timePassed);

		if (DetectCollision(_dynamicObject))
		{
			_dynamicObject->SetY(yTmp);

			_dynamicObject->speedVec[1] *= 0.5;
		}
	}
};

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
	MoveObject(_timePassed, currentLevel->player);

	//----- Camera ---------
	if (currentLevel->camera->followPlayer)
	{
		currentLevel->camera->x = currentLevel->player->x;
		currentLevel->camera->y = currentLevel->player->y;

		currentLevel->player->scrX = currentLevel->camera->offsetX;
		currentLevel->player->scrY = currentLevel->camera->offsetY;
	}
	else
	{
		currentLevel->player->scrX = currentLevel->player->x - currentLevel->camera->x + currentLevel->camera->offsetX;
		currentLevel->player->scrY = currentLevel->player->y - currentLevel->camera->y + currentLevel->camera->offsetY;
	}
		
	for (vecIt = 0; vecIt != currentLevel->blocks.size(); vecIt++) //Blocks
	{
		block = currentLevel->blocks.at(vecIt);

		block->scrX = block->x - currentLevel->camera->x + currentLevel->camera->offsetX;
		block->scrY = block->y - currentLevel->camera->y + currentLevel->camera->offsetY;
	}
	//---------------------
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
	currentLevel->player->maxAccel[0] = 50.0f;	
	currentLevel->player->maxAccel[1] = 50.0f;

	currentLevel->player->maxDeccel[0] = 100.0f;
	currentLevel->player->maxDeccel[1] = 100.0f;

	currentLevel->player->maxSpeed[0] = 80.0f;
	currentLevel->player->maxSpeed[1] = 80.0f;

	currentLevel->player->width = 50.0f;
	currentLevel->player->height = 50.0f;

	currentLevel->player->x = 20.0f;
	currentLevel->player->y = 20.0f;

	currentLevel->player->drawHitbox = true;
	currentLevel->player->collidable = true;

	//Blocks
	currentLevel->AddBlock(20, 200, 100, 200, true, true, false);
	currentLevel->AddBlock(400, 20, 200, 100, true, true, false);

	//Camera
	currentLevel->camera = new Camera(150, 400, config->RES_X, config->RES_Y);

	currentLevel->camera->followPlayer = true;

	this->render->showFps = true;
	this->render->drawCollisions = true;

	this->devMode = false;

	return true;
}