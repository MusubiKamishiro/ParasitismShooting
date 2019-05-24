#pragma once
#include "../CharacterObject.h"
#include "../../Geometry.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Player;
//class Enemy;
class EnemyFactory;
class ShotFactory;


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
	int shooter;
	int time;
	std::string shotType;
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

		double SetTracking(std::string shotType, Vector2f pos,int shooter,double oldangle);

public:
	virtual ~Shot();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Delete() = 0;

	int GetShooter()const;
	std::string GetShotName()const;
};

