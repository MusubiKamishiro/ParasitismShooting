#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// ƒ{ƒX
class Gusokun : public Enemy
{
	friend EnemyFactory;
private:
	// ¼İ¸ŞÙÄİ‚ÌŒˆ‚Ü‚è
	Gusokun(const Player& player);		// ¶¬‹Ö~
	Gusokun(const Gusokun&);				// ºËß°‹Ö~
	void operator=(const Gusokun&);	// ‘ã“ü‹Ö~

	Enemy* Clone();

	void Move();
	void Die();
	void Stunning();
	void StunDamage();
	void Damage();

	void (Gusokun::*updater)();

	const Player& player;

	bool flag;
public:
	~Gusokun();

	void Update();
	void Draw(int time);
};
