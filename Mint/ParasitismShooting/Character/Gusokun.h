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
	// �ݸ���݂̌��܂�
	Gusokun(const Player& player);		// �����֎~
	Gusokun(const Gusokun&);				// ��߰�֎~
	void operator=(const Gusokun&);	// ����֎~

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
