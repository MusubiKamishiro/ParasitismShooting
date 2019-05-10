#pragma once
#include "../../Geometry.h"
#include <list>
#include <map>

class Shot;

typedef std::list<Shot*> Legion;	// �e�̏W���̂̌^

class ShotFactory
{
private:
	const Shot& shot;
	
	std::map<std::string, Shot*> originalShot;	// �e�̌��ƂȂ�map�̍쐬
	Legion legion;

public:
	ShotFactory(const Shot& shot);
	~ShotFactory();

	// �e�����
	// enemyname...�e�̖��O
	Shot* Create(const char* enemyname, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed);
	
	// �e�̏W���̂�Ԃ�
	Legion& GetLegion();
};

