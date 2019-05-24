#pragma once
#include "../../Geometry.h"
#include <list>
#include <map>

class Shot;
class Player;
class EnemyFactory;

typedef std::list<Shot*> SLegion;	// �e�̏W���̂̌^

class ShotFactory
{
private:
	const Player& player;
	const EnemyFactory& enemyfactory;
	
	std::map<std::string, Shot*> originalShot;	// �e�̌��ƂȂ�map�̍쐬
	SLegion legion;

	int up;
	int right;
	int left;
	int down;

	float angle;
public:
	ShotFactory(const Player& player, const EnemyFactory& enemyfactory);
	~ShotFactory();

	// �e�����
	// shotType...�e�̖��O
	Shot* Create(std::string shotType, Vector2f pos, int Speed, int movePtn, int level, int shooter);

	// �e�̏W���̂�Ԃ�
	SLegion& GetLegion();
	// ���̂��̂ɓ��������e������
	void ShotDelete();
	void OutofScreen(void);

	double SetAngle(std::string shotType, Vector2f pos, int shooter,int cnt,int);
	double SetTracking(std::string shotType, Vector2f pos,int shooter);
};

