#include "Level.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

BaseObject::BaseObject()
{
	x = 0.0f;
	y = 0.0f;

	scrX = 0.0f;
	scrY = 0.0f;

	width = 0.0f;
	height = 0.0f;

	drawHitbox = false;
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
	if (this->accelVec[0]) //If accelarating
	{
		if (this->speedVec[0] < this->maxSpeed[0] && this->speedVec[0] * -1 < this->maxSpeed[0])
			this->speedVec[0] += this->accelVec[0] * _timePassed;

		this->x += this->speedVec[0] * _timePassed;
	}
	else if (this->speedVec[0]) //If decelarating
	{
		if (this->speedVec[0] > 0)
		{
			this->speedVec[0] -= this->maxDeccel[0] * _timePassed;

			if (this->speedVec[0] < 0) this->speedVec[0] = 0;

			this->x += this->speedVec[0] * _timePassed;
		}
		else
		{
			this->speedVec[0] += this->maxDeccel[0] * _timePassed;

			if (this->speedVec[0] > 0) this->speedVec[0] = 0;

			this->x += this->speedVec[0] * _timePassed;
		}
	}

	// Y - axis
	if (this->accelVec[1]) //If accelarating
	{
		if (this->speedVec[1] < this->maxSpeed[1] && this->speedVec[1] * -1 < this->maxSpeed[1])
			this->speedVec[1] += this->accelVec[1] * _timePassed;

		this->y -= this->speedVec[1] * _timePassed;
	}
	else if (this->speedVec[1]) //If decelarating
	{
		if (this->speedVec[1] > 0)
		{
			this->speedVec[1] -= this->maxDeccel[1] * _timePassed;

			if(this->speedVec[1] < 0) this->speedVec[1] = 0;

			this->y -= this->speedVec[1] * _timePassed;
		}
		else
		{
			this->speedVec[1] += this->maxDeccel[1] * _timePassed;

			if (this->speedVec[1] > 0) this->speedVec[1] = 0;

			this->y -= this->speedVec[1] * _timePassed;
		}
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

	devMode = false;
	showFps = false;
}

Level::~Level()
{
	int vecIt;

	delete player;
	delete camera;

	//Delete blocks
	for (vecIt = 0; vecIt != blocks.size(); vecIt++)
	{
		delete blocks.at(vecIt);
		blocks.at(vecIt) = NULL;
	}	
}

void Level::AddBlock(double _x, double _y, double _width, double _height)
{
	block = new Block();

	block->x = _x;
	block->y = _y;
	block->width = _width;
	block->height = _height;

	block->drawHitbox = true;
	block->clip = true;
	block->destructable = false;

	//Add to list
	blocks.push_back(block);
}