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

	//shottype
	//bombtype

	//std::string _nowActionName;	// ���ݍĐ����̱���ݖ�
	//int _nowCutIdx;				// ���ݕ\�����̶�Ĕԍ�
	//unsigned int _flame;		// ���̶�Ĕԍ��ɂ�����o�ߎ���

public:
	///// ��׸����\��
	//void Draw(int _img);
	///// �������`��\��
	//void DebugDraw();

	CharacterObject();
	virtual ~CharacterObject();

	Vector2f GetPos()const;
};

