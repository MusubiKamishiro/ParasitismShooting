#pragma once
//#include <string>
#include <vector>
#include <map>
#include "../Geometry.h"


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

	void SetCharaSize(const float& size);

	int HP;			// �̗�
	int SP;			// �X�^�~�i

	int movePtn;	// �ړ��p�^�[��
	int cnt;		// �L�����N�^�[���Ƃ̃J�E���g
	int wait;		// �L�����N�^�[���Ƃ̑ҋ@����

	bool lifeFlag;	// �����Ă邩����ł邩

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
	Rect GetRects(Rect& rect)const;
	std::vector<ActRect> GetActRect()const;

	Vector2f GetPos()const;
	int GetHP()const;
	bool GetLifeFlag()const;
};

