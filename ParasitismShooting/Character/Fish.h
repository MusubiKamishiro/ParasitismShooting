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
	
	
	void (Fish::*updater)();

	const Player& player;

	int wait;

public:
	~Fish();

	void Update();
	void Draw();
};