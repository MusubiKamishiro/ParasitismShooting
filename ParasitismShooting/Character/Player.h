#pragma once
#include "../Geometry.h"
#include "CharacterObject.h"
#include <memory>

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

	void NotOutOfRange();		// �͈͊O�ɍs�����Ȃ�

	CharaData originData;		// �񐶑O�̌��X�̃f�[�^
	Vector2f startPos;			// �J�n���W

	bool parasFlag;				// �񐶒����ۂ�
	bool pinchFlag;				// �񐶉������ꂽ��true�ɂȂ�

	int icount;
	int ccount;
	int efect;

	// �ړ��͈͌��E�l
	int up;
	int right;
	int left;
	int down;

	std::shared_ptr<GameScreen> gs;
	
public:
	Player();
	~Player();

	void Update(const Peripheral &p);
	void Draw(const int& time);
};

