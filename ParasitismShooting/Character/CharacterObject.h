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

	//// ����ݐ؂�ւ�
	//void ChangeAction(const char* name);
	//// ��Ұ��݂��ڰт�1�i�߂�
	//bool ProceedAnimationFile();

	//// ̧�ق̓ǂݍ���
	//void ReadActionFile(const char* actionPath);

	//bool _isTurn;		// ���]�׸�

public:
	//bool _isAerial;			// ���׸�


	///// ��׸����\��
	//void Draw(int _img);
	///// �������`��\��
	//void DebugDraw();
	//// ��`�̏������炤
	//Rect GetActionRects(Rect& rc)const;

	//std::vector<ActRect> GetAcutRect()const;

	//Position2f GetPos()const;

	CharacterObject();
	virtual ~CharacterObject();

	Vector2f GetPos()const;
};

