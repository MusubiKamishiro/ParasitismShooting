#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// É{ÉX
class Gusokun : public Enemy
{
	friend EnemyFactory;
private:
	Gusokun(const Player& player);	// ê∂ê¨ã÷é~
	Gusokun(const Gusokun&);		// ∫Àﬂ∞ã÷é~
	void operator=(const Gusokun&);	// ë„ì¸ã÷é~

	Enemy* Clone();

	void Move();
	void Die();
	void Stunning();
	void StunDamage();
	void Damage();

	void orginalMove(int movePtn, Vector2f & pos, float speed, int cnt, int wait, int shotCnt, int charSP, bool& ShotReady);

	void (Gusokun::*updater)();

	const Player& player;

	Vector2f basePos;
	float vecAngle;
public:
	~Gusokun();

	void Update();
	void Draw(int time);
};
