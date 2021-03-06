#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// CV
class Ebi : public Enemy
{
	friend EnemyFactory;
private:
	Ebi(const Player& player);		// Ά¬Φ~
	Ebi(const Ebi&);				// ΊΛί°Φ~
	void operator=(const Ebi&);	// γόΦ~

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
