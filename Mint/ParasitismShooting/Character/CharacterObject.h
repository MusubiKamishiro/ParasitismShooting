#pragma once
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

// �L�����N�^�[�����ׂ��f�[�^
// �񐶂̍ۂɎg�p����
struct CharaData
{
	ActionData actData;		// �A�N�V�����f�[�^
	int img;				// �摜
	float charaSize;		// �L�����N�^�[�̊g�嗦
	int HP;					// �̗�
	int SP;					// �X�^�~�i
	float moveVel;			// �ړ���
	const char* shotType;	// �e�̖��O
	bool ShotReady;			// �V���b�g��ł��ǂ����̃t���O
};

// ��׸�����׽
class CharacterObject
{
protected:
	// ̧�ق̓ǂݍ���
	void ReadActionFile(const char* actionPath);
	// �A�j���[�V�����؂�ւ�
	void ChangeAction(const char* name);

	void SetCharaSize(const float& size);


	CharaData charaData;

	int movePtn;	// �ړ��p�^�[��
	int cnt;		// �L�����N�^�[���Ƃ̃J�E���g
	int wait;		// �L�����N�^�[���Ƃ̑ҋ@����

	bool lifeFlag;	// �����Ă邩����ł邩
	bool shotReady;

	Vector2f pos;	// ���W
	Vector2f vel;	// �ړ����x
	Rect rect;		// ���S�A���ƍ���

	//shottype

	std::string nowActionName;	// ���ݍĐ����̱���ݖ�
	unsigned int nowCutIdx;		// ���ݕ\�����̶�Ĕԍ�
	unsigned int flame;			// ���̶�Ĕԍ��ɂ�����o�ߎ���

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
	
	CharaData GetCharaData()const;
	Vector2f GetPos()const;
	bool GetLifeFlag()const;
	bool GetShotReady()const;
};

