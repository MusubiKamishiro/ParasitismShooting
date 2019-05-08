#pragma once
//#include <string>
#include <vector>
#include <map>
#include "../Geometry.h"

enum class RectType
{
	box,		// ��
	circle,		// �Z
};

// ����݋�`��`
struct ActRect
{
	RectType rt;	// ��`�̌`
	Rect rc;		// ��,����
};

// �؂蔲�����
struct CutInfo
{
	Rect rect;						// �؂蔲����`
	Vector2 center;					// ���S�_
	int duration;					// �\������		// �����܂�28�޲�
	std::vector<ActRect> actrects;	// ����݋�`
};// 44�޲�
typedef std::vector<CutInfo> CutInfoes_t;

struct ActionInfo {
	bool isLoop;				// ٰ�߂���
	CutInfoes_t cuts;			// ��ď��z��
};
struct ActionData {
	std::string imgFilePath;					// �摜̧���߽
	std::map<std::string, ActionInfo> animInfo;	// ����ݏ��
};

// ��׸�����׽
class CharacterObject
{
protected:
	ActionData actData;
	// ̧�ق̓ǂݍ���
	void ReadActionFile(const char* actionPath);
	// �A�j���[�V�����؂�ւ�
	void ChangeAction(const char* name);

	int HP;			// �̗�
	int SP;			// �X�^�~�i

	Vector2f pos;	// ���W
	Vector2f vel;	// �ړ����x
	Rect rect;		// ���S�A���ƍ���

	int img;		// �摜
	//shottype
	//bombtype

	std::string nowActionName;	// ���ݍĐ����̱���ݖ�
	unsigned int nowCutIdx;		// ���ݕ\�����̶�Ĕԍ�
	unsigned int flame;			// ���̶�Ĕԍ��ɂ�����o�ߎ���

	float charaSize;

public:
	CharacterObject();
	virtual ~CharacterObject();

	// ��׸����\��
	void Draw(int img);
	// �������`��\��
	void DebugDraw(ActRect actrect);

	// ��`�̏������炤
	Rect GetRects()const;
	Vector2f GetPos()const;
};

