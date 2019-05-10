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

enum SHOTER
{
	PLAYER,
	ENEMY,
	MAX
};


typedef struct ShotST
{
	Vector2f pos;
	double angle;
	int Speed;
	int movePtn;
	int level;
	int shotPtn;
	int shooter;
	std::string shotname;
}shot_st;

class Shot : public CharacterObject
{
	friend ShotFactory;
protected:
	virtual Shot* Clone() = 0;

	Shot(const Player& player/*, const Enemy& enemy*/);

	Vector2f cneterPos;
	double angle;
	int Speed;
	int movePtn;
	int level;
	int shotPtn;
	int shooter;

public:
	virtual ~Shot();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

