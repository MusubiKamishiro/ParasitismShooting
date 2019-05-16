#pragma once
#include "../CharacterObject.h"
#include "../../Geometry.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Player;
class Enemy;
class ShotFactory;

enum SHOT_PTN
{
	WEAK,
	NORMAL,
	SHOTGUN,
	TRACKING,
	RADIATION,
	RANDOM,
	LASER,
	PTN_MAX

};

enum SHOOTER
{
	PLAYER,
	ENEMY,
	MAX
};


struct ShotST
{
	Vector2f cpos;
	double angle;
	int speed;
	int movePtn;
	int level;
	int shotPtn;
	int shooter;
	std::string shotname;
};

class Shot : public CharacterObject
{
	friend ShotFactory;
protected:
	virtual Shot* Clone() = 0;

	Shot(const Player& player/*, const Enemy& enemy*/);

	ShotST shotst;

public:
	virtual ~Shot();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Delete() = 0;

	int GetShooter()const;
	std::string GetShotName()const;
};

