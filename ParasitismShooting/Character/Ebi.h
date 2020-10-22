#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// äCòV
class Ebi : public Enemy
{
	friend EnemyFactory;
private:
	Ebi(const Player& player);		// ê∂ê¨ã÷é~
	Ebi(const Ebi&);				// ∫Àﬂ∞ã÷é~
	void operator=(const Ebi&);	// ë„ì¸ã÷é~

	Enemy* Clone();

	void Move();
	void Die();
	void Stunning();
	void StunDamage();
	void Damage();
	
	void (Ebi::*updater)();

	const Player& player;
public:
	~Ebi();

	void Update();
	void Draw(int time);
};
