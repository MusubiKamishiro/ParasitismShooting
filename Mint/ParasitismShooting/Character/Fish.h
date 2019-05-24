#pragma once
#include "Enemy.h"
#include "CharacterObject.h"
#include <memory>

class Player;
class EnemyFactory;
class EnemyActionPattern;

// ‹›
class Fish : public Enemy
{
	friend EnemyFactory;
private:
	// ¼İ¸ŞÙÄİ‚ÌŒˆ‚Ü‚è
	Fish(const Player& player);		// ¶¬‹Ö~
	Fish(const Fish&);				// ºËß°‹Ö~
	void operator=(const Fish&);	// ‘ã“ü‹Ö~

	Enemy* Clone();

	void Move();
	void Die();
	void Stunning();
	void StunDamage();
	void Damage();
	
	void (Fish::*updater)();

	const Player& player;

	bool flag;

	std::shared_ptr<EnemyActionPattern> eAction;
public:
	~Fish();

	void Update();
	void Draw(int time);
};
