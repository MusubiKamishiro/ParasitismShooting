#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// ��
class Fish : public Enemy
{
	friend EnemyFactory;
private:
	// �ݸ���݂̌��܂�
	Fish(const Player& player);		// �����֎~
	Fish(const Fish&);				// ��߰�֎~
	void operator=(const Fish&);	// ����֎~

	Enemy* Clone();

	void Move();
	void Die();
	void Stunning();
	void StunDamage();
	void Damage();
	
	void (Fish::*updater)();

	const Player& player;


public:
	~Fish();

	void Update();
	void Draw(int time);
};
