#pragma once
//#include <string>
#include <vector>
//#include <map>
#include "../Geometry.h"


// ��׸�����׽
class CharacterObject
{
protected:
	int HP;			// �̗�
	int SP;			// �X�^�~�i

	Vector2f pos;	// ���W
	Vector2f vel;	// �ړ����x
	Rect rect;		// ���S�A���ƍ���

	int img;		// �摜
	//shottype
	//bombtype

	//std::string nowActionName;	// ���ݍĐ����̱���ݖ�
	//unsigned int nowCutIdx;		// ���ݕ\�����̶�Ĕԍ�
	//unsigned int flame;			// ���̶�Ĕԍ��ɂ�����o�ߎ���

public:
	// ��׸����\��
	void Draw(int img);
	///// �������`��\��
	//void DebugDraw();

	CharacterObject();
	virtual ~CharacterObject();

	Vector2f GetPos()const;
};

