#pragma once
#include "../Geometry.h"

class EnemyActionPattern
{
public:
	EnemyActionPattern();
	~EnemyActionPattern();
	void ActPattern0(Vector2f &pos, float speed, int cnt, int wait);		// �㉺�ړ�
	void ActPattern1(void);		// ���E�ɗ�����
	void ActPattern2(void);		// ���@�ɓ��U���d�|����
	void ActPattern3(void);		// �g��ړ�
};
