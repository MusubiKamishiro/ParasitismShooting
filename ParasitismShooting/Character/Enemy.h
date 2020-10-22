#pragma once
#include "CharacterObject.h"
#include <memory>

class EnemyFactory;
class Player;
class EnemyActionPattern;

class Enemy : public CharacterObject
{
	friend EnemyFactory;
protected:
	virtual Enemy* Clone() = 0;

	Enemy(const Player& player);
	
	unsigned int score;

	std::shared_ptr< EnemyActionPattern> eAction;
public:
	virtual ~Enemy();

	virtual void Update() = 0;
	virtual void Draw(int time) = 0;
	virtual void Damage() = 0;
	virtual void Die() = 0;
	virtual void Stunning() = 0;
	virtual void StunDamage() = 0;
	void ShotStop();

	bool GetShotReady()const;
	unsigned int GetScore()const;
	bool nextStageFlag;
	bool bossFlag;
	bool scoreFlag;
	bool actFlag;
};
