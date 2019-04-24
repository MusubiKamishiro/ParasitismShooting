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
class Shot;

class Player : public CharacterObject
{
	friend GamePlayingScene;
private:
	// ��ԑJ�ڂ̂��߂̃����o�֐��|�C���^
	void (Player::*updater)(const Peripheral &p);
	void Move(const Peripheral &p);
	void ShotBullet(const Peripheral &p);	// �U��
	void Damage(const Peripheral &p);		// �_���[�W�������
	void Invincible(const Peripheral &p);	// ���G����
	void Die(const Peripheral &p);			// �G�@�ɓ������Ď���

	void NotOutOfRange();		// �͈͊O�ɍs�����Ȃ�

	Vector2f startPos;			// �J�n���W
	float moveVel;				// �ړ���
	int count;

	// �ړ��͈͌��E�l
	int up;
	int right;
	int left;
	int down;

	int img;

	int interval;

	std::shared_ptr<Shot> shot;
	
public:
	Player();
	~Player();

	void Update(const Peripheral &p);

	void Draw(Vector2f& pos, const int& time);
};

