#pragma once
#include "../Geometry.h"
#include <list>
#include <map>

class Enemy;
class Player;

typedef std::list<Enemy*> ELegion;	// �G�̏W���̂̌^

class EnemyFactory
{
private:
	const Player& player;
	
	std::map<std::string, Enemy*> originalEnemy;	// �G�̌��ƂȂ�map�̍쐬
	ELegion legion;

public:
	EnemyFactory(const Player& player);
	~EnemyFactory();

	// �G�����
	// enemyname...�G�̖��O
	Enemy* Create(const char * enemyname, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed);
	
	// �G�̏W���̂�Ԃ�
	ELegion& GetLegion();
	// �_���[�W�e�ɓ�������������
	void EnemyDelete();
};

