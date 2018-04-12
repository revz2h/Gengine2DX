#ifndef __LEVEL_H_INCLUDED__
#define __LEVEL_H_INCLUDED__

#include <vector>

class BaseObject
{

public:
	double x, x2, y, y2, z, width, height, scrX, scrY;
	bool drawHitbox, collidable, colliding, collidingTop, collidingBottom, collidingLeft, collidingRight;

	BaseObject();
	~BaseObject();
};

class StaticObject : public BaseObject
{

public:
	StaticObject();
	~StaticObject();
};

class Block : public StaticObject
{

public:
	double health, armor;
	bool destructable;

	Block();
	~Block();
};

class DynamicObject : public BaseObject
{

public:
	double speedVec[2], accelVec[2], maxSpeed[2], maxAccel[2], maxDeccel[2], mass;
	bool moving, accelarating, stoping;

	DynamicObject();
	~DynamicObject();

	void SetX(double _x);
	void SetY(double _y);
};

class Player : public DynamicObject
{

public:
	Player();
	~Player();
};

class Npc : public DynamicObject
{

public:
	Npc();
	~Npc();

	bool MoveTo(double _x, double _y);
};

class Camera : public BaseObject
{
public:
	bool followPlayer;
	double offsetX, offsetY;

	Camera(double _x, double _y, double _width, double _height);
	~Camera();
};

class Level
{
public:
	Player* player;
	Camera*	camera;

	std::vector<Block*> blocks;
	Block* block;

	Level();
	~Level();

	void AddBlock(double _x, double _y, double _width, double _height, bool _drawHitbox, bool _collidable, bool _destructable);
};
#endif