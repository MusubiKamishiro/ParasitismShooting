#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// �{�X
class Boss : public Enemy
{
	friend EnemyFactory;
private:
	// �ݸ���݂̌��܂�
	Boss(const Player& player);		// �����֎~
	Boss(const Boss&);				// ��߰�֎~
	void operator=(const Boss&);	// ����֎~

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
