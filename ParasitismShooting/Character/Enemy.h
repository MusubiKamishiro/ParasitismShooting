#pragma once
#include "CharacterObject.h"

class EnemyFactory;
class Player;

class Enemy : public CharacterObject
{
	friend EnemyFactory;
protected:
	virtual Enemy* Clone() = 0;

	Enemy(const Player& player);

public:
	virtual ~Enemy();

	virtual void Update() = 0;
	virtual void Draw(int time) = 0;
	virtual void Damage() = 0;
	virtual void Die() = 0;
	virtual void Stunning() = 0;
	virtual void StunDamage() = 0;
};

