#pragma once
#include "../CharacterObject.h"
#include "../../Geometry.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Player;
//class Enemy;
class EnemyFactory;
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
	float angle;
	float speed;
	int power;
	int movePtn;
	int level;
	int shotPtn;
	int shooter;
	int time;
	std::string shotType;
	std::string shotTypeSub;
};

class Shot : public CharacterObject
{
	friend ShotFactory;
private:
	const Player& player;
	const EnemyFactory& enemyfactory;
protected:
	virtual Shot* Clone() = 0;

	Shot(const Player& player, const EnemyFactory& enemyfactory/*, const Enemy& enemy*/);

	ShotST shotst;

	float SetTracking(std::string shotType, Vector2f pos, int shooter, float oldangle);

	float GetAtan2(int shooter, float oldangle);

public:
	virtual ~Shot();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Delete() = 0;

	int GetShooter()const;
	std::string GetShotName()const;
};

