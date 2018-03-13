#ifndef __LEVEL_H_INCLUDED__
#define __LEVEL_H_INCLUDED__

#include <vector>

class BaseObject
{

public:
	double x, y, width, height, scrX, scrY;
	bool drawHitbox;

	BaseObject();
	~BaseObject();
};

class StaticObject : public BaseObject
{

public:
	double health, armor;
	bool clip, destructable;

	StaticObject();
	~StaticObject();
};

class Block : public StaticObject
{
public:
	Block();
	~Block();
};

class DynamicObject : public BaseObject
{

public:
	double speedVec[2], accelVec[2], maxSpeed[2], maxAccel[2], maxDeccel[2], mass;
	bool moving, accelarating, stoping;

	void MoveObject(double &_timePassed);

	DynamicObject();
	~DynamicObject();
};

class Player : public DynamicObject
{

public:
	Player();
	~Player();
};

class Camera : public BaseObject
{
public:
	bool followPlayer;

	Camera();
	~Camera();
};

class Level
{
public:
	Player* player;
	Camera*	camera;

	std::vector<Block*> blocks;
	bool devMode, showFps;
	Block* block;

	Level();
	~Level();

	void AddBlock(double _x, double _y, double _width, double _height);
};
#endif