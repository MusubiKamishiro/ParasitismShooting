#pragma once
#include <memory>
#include "../Geometry.h"
#include "CharacterObject.h"
#include "../KeyConfig.h"


enum Dir
{
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

class Peripheral;
class GamePlayingScene;
class GameScreen;


class Player : public CharacterObject
{
	friend GamePlayingScene;
private:
	// ��ԑJ�ڂ̂��߂̃����o�֐��|�C���^
	void (Player::*updater)(const Peripheral &p);
	void Move(const Peripheral &p);
	void Damage(const Peripheral &p);		// �_���[�W�������
	void Invincible(const Peripheral &p);	// ���G����
	void Die(const Peripheral &p);			// �G�@���͒e�ɓ������Ď���
	void Reborn(const Peripheral &p);		// ����
	void Parasitic(const Peripheral &p, const CharaData& cdata);	// ��
	void ParasiticCancel(const Peripheral &p);		// �񐶉���

	void Init();	// 2�̃R���X�g���N�^�̋��ʕ���
	void NotOutOfRange();		// �͈͊O�ɍs�����Ȃ�

	CharaData originData;		// �񐶑O�̌��X�̃f�[�^
	Vector2f startPos;			// �J�n���W

	bool parasFlag;				// �񐶒����ۂ�
	bool pinchFlag;				// �񐶉������ꂽ��true�ɂȂ�

	int icount;
	int ccount;

	// �ړ��͈͌��E�l
	int up;
	int right;
	int left;
	int down;

	std::shared_ptr<GameScreen> gs;
	KeyConfig& key = KeyConfig::Instance();
	
public:
	// �X�e�[�W1�Ŏg���C���X�^���X(�����͉��ɂ��񐶂��Ă��Ȃ�����)
	Player();
	// �X�e�[�W2�ȍ~�Ŏg���C���X�^���X(�O�X�e�[�W�̍Ō�̊񐶏�Ԃ������Ă���)
	Player(const CharaData& cdata);
	~Player();

	void Update(const Peripheral &p);
	void Draw(const int& time);
	void ParasDraw(const int& time);
};

