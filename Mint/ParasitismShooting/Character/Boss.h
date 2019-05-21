#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// É{ÉX
class Boss : public Enemy
{
	friend EnemyFactory;
private:
	// º›∏ﬁŸƒ›ÇÃåàÇ‹ÇË
	Boss(const Player& player);		// ê∂ê¨ã÷é~
	Boss(const Boss&);				// ∫Àﬂ∞ã÷é~
	void operator=(const Boss&);	// ë„ì¸ã÷é~

	Enemy* Clone();

	void Move();
	void Die();
	void Stunning();
	void StunDamage();
	void Damage();
	
	void (Boss::*updater)();

	const Player& player;

	bool flag;
public:
	~Boss();

	void Update();
	void Draw(int time);
};
