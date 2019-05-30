#pragma once
#include <iostream>
#include "../Geometry.h"
class Player;

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
	void Update(int movePtn, Vector2f & pos, float moveVel, int cnt, int wait, int shotCnt, int charSP, bool& ShotReady);
private:
	void UpDown(Vector2f &pos, float moveVel, int cnt, int wait);		// �㉺�ړ�
	void LeftRight(Vector2f &pos, float moveVel, int cnt, int wait);		// ���E�ɗ�����
	void Rush(Vector2f &pos, float moveVel, int cnt, int wait);		// ���@�ɓ��U���d�|����
	void Wavy(Vector2f &pos, float moveVel, int cnt, int wait);		// �g��ړ�
	void Stun(Vector2f &pos, float moveVel);		// �C����

	void(EnemyActionPattern::*movementPtn[MOVEMENT_PTN_MAX])(Vector2f &pos, float moveVel, int cnt, int wait);

	int x = 1;
};
