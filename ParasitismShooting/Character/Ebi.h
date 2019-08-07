#pragma once
#include "Enemy.h"
#include "CharacterObject.h"

class Player;
class EnemyFactory;

// �C�V
class Ebi : public Enemy
{
	friend EnemyFactory;
private:
	// �ݸ���݂̌��܂�
	Ebi(const Player& player);		// �����֎~
	Ebi(const Ebi&);				// ��߰�֎~
	void operator=(const Ebi&);	// ����֎~

	Enemy* Clone();

	void Move();
	void Die();
	void Stunning();
	void StunDamage();
	void Damage();
	
	void (Ebi::*updater)();

	const Player& player;
public:
	~Ebi();

	void Update();
	void Draw(int time);
};
