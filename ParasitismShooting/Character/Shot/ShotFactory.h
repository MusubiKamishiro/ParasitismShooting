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
	int cnt = 0;
	const Player& player;
	
	std::map<std::string, Shot*> originalShot;	// �e�̌��ƂȂ�map�̍쐬
	SLegion legion;

public:
	ShotFactory(const Player& player/*, const Enemy& enemy*/);
	~ShotFactory();

	// �e�����
	// enemyname...�e�̖��O
	Shot* Create(const char * shotname,Vector2f pos, float angle, int Speed, int movePtn, int level, int shotPtn, int shooter);
	
	// �e�̏W���̂�Ԃ�
	SLegion& GetLegion();
};

