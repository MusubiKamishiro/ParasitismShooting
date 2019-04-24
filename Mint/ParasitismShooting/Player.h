#pragma once
#include "Geometry.h"
//#include "CharacterObject.h"
#include <memory>
//#include <vector>

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

class Player// : public CharacterObject
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

	Vector2 startPos;			// �J�n���W
	Vector2 pos;				// ���ݍ��W
	Vector2 vel;				// �ړ����x
	float moveVel;				// �ړ���
	int life;					// �̗�
	int count;

	// �ړ��͈͌��E�l
	int up;
	int right;
	int left;
	int down;

	int img;

	int cnt;

	std::shared_ptr<Shot> shot;
	
public:
	Player();
	~Player();

	void Update(const Peripheral &p);

	Vector2 GetPos()const;
	void Draw(Vector2& pos, int time);
};

