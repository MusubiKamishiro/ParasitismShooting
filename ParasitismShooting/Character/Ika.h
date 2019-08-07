#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// ‰G‘¯
class Ika : public Enemy
{
	friend EnemyFactory;
private:
	// ¼İ¸ŞÙÄİ‚ÌŒˆ‚Ü‚è
	Ika(const Player& player);		// ¶¬‹Ö~
	Ika(const Ika&);				// ºËß°‹Ö~
	void operator=(const Ika&);	// ‘ã“ü‹Ö~

	Enemy* Clone();

	void Move();
	void Die();
	void Stunning();
	void StunDamage();
	void Damage();
	
	void (Ika::*updater)();

	const Player& player;
public:
	~Ika();

	void Update();
	void Draw(int time);
};
