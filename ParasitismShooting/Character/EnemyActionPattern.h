#pragma once
#include <iostream>
#include "../Geometry.h"
class Player;

//typedef void(EnemyActionPattern::*movePtn[])(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag);

enum MovementPTN
{
	UpDown,
	LeftRight,
	Rush,
	Wavy,
	Stun,
	MOVEMENT_PTN_MAX
};

class EnemyActionPattern
{
public:
	EnemyActionPattern();
	~EnemyActionPattern();
	void Update(int movePtn, Vector2f &pos, float Speed, int cnt, int wait, bool lifeFlag);
private:
	void UpDown(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag);		// �㉺�ړ�
	void LeftRight(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag);		// ���E�ɗ�����
	void Rush(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag);		// ���@�ɓ��U���d�|����
	void Wavy(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag);		// �g��ړ�
	void Stun(Vector2f &pos, float speed);		// �C����

	void(EnemyActionPattern::*movementPtn[MOVEMENT_PTN_MAX])(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag)/* = { &EnemyActionPattern::UpDown,&EnemyActionPattern::LeftRight }*/;
};
