#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// ãõ
class Fish : public Enemy
{
	friend EnemyFactory;
private:
	Fish(const Player& player);		// ê∂ê¨ã÷é~
	Fish(const Fish&);				// ∫Àﬂ∞ã÷é~
	void operator=(const Fish&);	// ë„ì¸ã÷é~

	Enemy* Clone();

	void Move();
	void Die();
	void Stunning();
	void StunDamage();
	void Damage();
	
	void (Fish::*updater)();

	const Player& player;
public:
	~Fish();

	void Update();
	void Draw(int time);
};
