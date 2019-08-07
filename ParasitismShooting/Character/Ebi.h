#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// ŠC˜V
class Ebi : public Enemy
{
	friend EnemyFactory;
private:
	// ¼İ¸ŞÙÄİ‚ÌŒˆ‚Ü‚è
	Ebi(const Player& player);		// ¶¬‹Ö~
	Ebi(const Ebi&);				// ºËß°‹Ö~
	void operator=(const Ebi&);	// ‘ã“ü‹Ö~

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
