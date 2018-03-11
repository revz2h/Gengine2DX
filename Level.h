#ifndef __LEVEL_H_INCLUDED__
#define __LEVEL_H_INCLUDED__

class BaseObject
{

public:
	double x, y, width, height;
	bool drawHitbox;

	BaseObject();
	~BaseObject();
};

class DynamicObject : public BaseObject
{

public:
	double speedVec[2], accelVec[2], maxSpeed[2], maxAccel[2], maxDeccel[2]; //Seems faster using arrays, than vector objects?
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

	Camera();
	~Camera();
};

class Level
{
public:
	Player* player;
	bool devMode, showFps;

	Level();
	~Level();
};
#endif