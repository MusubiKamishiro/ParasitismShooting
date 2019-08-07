#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// �G��
class Ika : public Enemy
{
	friend EnemyFactory;
private:
	// �ݸ���݂̌��܂�
	Ika(const Player& player);		// �����֎~
	Ika(const Ika&);				// ��߰�֎~
	void operator=(const Ika&);	// ����֎~

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
