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
	FadeOut,
	MOVEMENT_PTN_MAX
};

class EnemyActionPattern
{
public:
	EnemyActionPattern();
	~EnemyActionPattern();
	void Update(int movePtn, Vector2f & pos, float speed, int cnt, int wait, int shotCnt, int charSP, bool& ShotReady);
private:
	void UpDown(Vector2f &pos, float speed, int cnt, int wait);		// �㉺�ړ�
	void LeftRight(Vector2f &pos, float speed, int cnt, int wait);	// ���E�ɗ�����
	void Rush(Vector2f &pos, float speed, int cnt, int wait);		// ���@�ɓ��U���d�|����
	void Wavy(Vector2f &pos, float speed, int cnt, int wait);		// �g��ړ�
	void FadeOut(Vector2f &pos, float speed, int cnt, int wait);
	void Stun(Vector2f &pos, float speed);		// �C����

	void(EnemyActionPattern::*movementPtn[MOVEMENT_PTN_MAX])(Vector2f &pos, float speed, int cnt, int wait);

	int x = 1;
};
