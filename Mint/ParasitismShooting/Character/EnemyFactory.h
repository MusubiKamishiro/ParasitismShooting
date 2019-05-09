#pragma once
#include "../Geometry.h"
#include <list>
#include <map>

class Enemy;
class Player;

typedef std::list<Enemy*> Legion;	// �G�̏W���̂̌^

class EnemyFactory
{
private:
	const Player& player;
	
	std::map<std::string, Enemy*> originalEnemy;	// �G�̌��ƂȂ�map�̍쐬
	Legion legion;

public:
	EnemyFactory(const Player& player);
	~EnemyFactory();

	// �G�����
	// enemyname...�G�̖��O
	Enemy* Create(const char * enemyname, Vector2f pos, int movePtn, int cnt, int wait);
	
	// �G�̏W���̂�Ԃ�
	Legion& GetLegion();
};

