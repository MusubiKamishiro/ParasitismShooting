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

	int up;
	int right;
	int left;
	int down;

public:
	EnemyFactory(const Player& player);
	~EnemyFactory();

	// �G�����
	// enemyname...�G�̖��O
	Enemy* Create(const char * enemyname, const char * shotType, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed, int shotCnt, int shotlevel);

	// �G�̏W���̂�Ԃ�
	ELegion& GetLegion();

	Vector2f GetLegionBeginCharPos()const;
	// �_���[�W�e�ɓ�������������
	void EnemyDelete();
	void OutofScreen();
};

