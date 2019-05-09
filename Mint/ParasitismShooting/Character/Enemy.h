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
	virtual void Draw() = 0;
	//virtual void Damage() = 0;
};

