#pragma once
#include "../../Geometry.h"
#include <list>
#include <map>

class Shot;
class Player;
class Enemy;

typedef std::list<Shot*> SLegion;	// �e�̏W���̂̌^

class ShotFactory
{
private:
	const Player& player;
	
	std::map<std::string, Shot*> originalShot;	// �e�̌��ƂȂ�map�̍쐬
	SLegion legion;

public:
	ShotFactory(const Player& player/*, const Enemy& enemy*/);
	~ShotFactory();

	// �e�����
	// enemyname...�e�̖��O
	Shot* Create(const char* enemyname, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed);
	
	// �e�̏W���̂�Ԃ�
	SLegion& GetLegion();
};

