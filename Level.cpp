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

	collidingTop = false;
	collidingBottom = false;
	collidingLeft = false;
	collidingRight = false;
}

BaseObject::~BaseObject()
{
}

StaticObject::StaticObject()
{
}

StaticObject::~StaticObject() 
{

}

Block::Block()
{
	health = 1;
	armor = 1;
	destructable = false;
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

void DynamicObject::SetX(double _x)
{
	x = _x;
	x2 = x + width;
}

void DynamicObject::SetY(double _y)
{
	y = _y;
	y2 = y + height;
}

Player::Player()
{
}

Player::~Player()
{
}

Npc::Npc()
{

}

Npc::~Npc()
{

}

bool Npc::MoveTo(double _x, double _y)
{
	return false;
}

Level::Level()
{
	player = new Player();

	block = NULL;
	camera = NULL;
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