#include "Level.h"

Camera::Camera(double _x, double _y, double _width, double _height)
{
	x = _x;
	y = _y;

	width = _width;
	height = _height;

	offsetX = width / 2;
	offsetY = height / 2;

	followPlayer = true;
}

Camera::~Camera()
{
}

BaseObject::BaseObject()
{
	x = 0.0f;
	y = 0.0f;
	z = 1.0f;

	x2 = 0.0f;
	y2 = 0.0f;

	scrX = 0.0f;
	scrY = 0.0f;

	width = 0.0f;
	height = 0.0f;

	drawHitbox = false;
	collidable = false;
	colliding = false;
}

BaseObject::~BaseObject()
{
}

StaticObject::StaticObject()
{
	health = 1;
	armor = 1;
	destructable = false;
}

StaticObject::~StaticObject() 
{

}

Block::Block()
{

}

Block::~Block()
{

}

DynamicObject::DynamicObject()
{
	speedVec[0] = 0.0f;
	speedVec[1] = 0.0f;

	accelVec[0] = 0.0f;
	accelVec[1] = 0.0f;

	maxSpeed[0] = 0.0f;
	maxSpeed[1] = 0.0f;

	maxAccel[0] = 0.0f;
	maxAccel[1] = 0.0f;

	maxDeccel[0] = 0.0f;
	maxDeccel[1] = 0.0f;

	mass = 0.0f;

	moving = false;
	accelarating = false;
	stoping = false;	
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::MoveObject(double &_timePassed)
{
	// X - axis
	if (accelVec[0]) //If accelarating
	{
		if (speedVec[0] < maxSpeed[0] && speedVec[0] * -1 < maxSpeed[0])
			speedVec[0] += accelVec[0] * _timePassed;

		x += speedVec[0] * _timePassed;

		x2 = x + width;
	}
	else if (speedVec[0]) //If decelarating
	{
		if (speedVec[0] > 0)
		{
			speedVec[0] -= maxDeccel[0] * _timePassed;

			if (speedVec[0] < 0) speedVec[0] = 0;

			x += speedVec[0] * _timePassed;
		}
		else
		{
			speedVec[0] += maxDeccel[0] * _timePassed;

			if (speedVec[0] > 0) speedVec[0] = 0;

			x += speedVec[0] * _timePassed;			
		}

		x2 = x + width;
	}

	// Y - axis
	if (accelVec[1]) //If accelarating
	{
		if (speedVec[1] < maxSpeed[1] && speedVec[1] * -1 < maxSpeed[1])
			speedVec[1] += accelVec[1] * _timePassed;

		y -= speedVec[1] * _timePassed;

		y2 = y + height;
	}
	else if (speedVec[1]) //If decelarating
	{
		if (speedVec[1] > 0)
		{
			speedVec[1] -= maxDeccel[1] * _timePassed;

			if(speedVec[1] < 0) speedVec[1] = 0;

			y -= speedVec[1] * _timePassed;			
		}
		else
		{
			speedVec[1] += maxDeccel[1] * _timePassed;

			if (speedVec[1] > 0) speedVec[1] = 0;

			y -= speedVec[1] * _timePassed;
		}

		y2 = y + height;
	}
};

Player::Player()
{
}

Player::~Player()
{
}

Level::Level()
{
	player = new Player();

	block = NULL;
	camera = NULL;

	devMode = false;
	showFps = false;
}

Level::~Level()
{
	int vecIt;

	delete block;
	delete player;
	delete camera;

	//Delete blocks
	for (vecIt = 0; vecIt != blocks.size(); vecIt++)
	{
		delete blocks.at(vecIt);
		blocks.at(vecIt) = NULL;
	}	
}

void Level::AddBlock(double _x, double _y, double _width, double _height, bool _drawHitbox, bool _collidable, bool _destructable)
{
	block = new Block();

	block->x = _x;
	block->y = _y;
	block->width = _width;
	block->height = _height;

	block->x2 = _x + _width;
	block->y2 = _y + _height;

	block->drawHitbox = _drawHitbox;
	block->collidable = _collidable;
	block->destructable = _destructable;

	//Add to list
	blocks.push_back(block);
}