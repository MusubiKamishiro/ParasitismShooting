#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// �{�X
class Gusokun : public Enemy
{
	friend EnemyFactory;
private:
	Gusokun(const Player& player);	// �����֎~
	Gusokun(const Gusokun&);		// ��߰�֎~
	void operator=(const Gusokun&);	// ����֎~

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
