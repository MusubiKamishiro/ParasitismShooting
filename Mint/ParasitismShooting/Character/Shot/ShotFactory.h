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

	int up;
	int right;
	int left;
	int down;
public:
	ShotFactory(const Player& player/*, const Enemy& enemy*/);
	~ShotFactory();

	// �e�����
	// enemyname...�e�̖��O
	Shot* Create(const char * shotname,Vector2f pos, int Speed, int movePtn, int level, int shooter);
	
	// �e�̏W���̂�Ԃ�
	SLegion& GetLegion();
	// ���̂��̂ɓ��������e������
	void ShotDelete();
	void OutofScreen(void);

	double SetAngle(Vector2f pos, int shooter);
};

