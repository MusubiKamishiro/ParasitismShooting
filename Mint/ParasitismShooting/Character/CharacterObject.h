#pragma once
//#include <string>
#include <vector>
//#include <map>
#include "../Geometry.h"


// ��׸�����׽
class CharacterObject
{
protected:
	// ̧�ق̓ǂݍ���
	void ReadActionFile(const char* actionPath);

	int HP;			// �̗�
	int SP;			// �X�^�~�i

	int movePtn;	// �ړ��p�^�[��
	int cnt;		// �L�����N�^�[���Ƃ̃J�E���g
	int wait;		// �L�����N�^�[���Ƃ̑ҋ@����

	bool flag;		// �����t���O

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
	CharacterObject();
	virtual ~CharacterObject();

	// ��׸����\��
	void Draw(int img);
	// �������`��\��
	void DebugDraw();

	// ��`�̏������炤
	Rect GetRects()const;
	Vector2f GetPos()const;
};

