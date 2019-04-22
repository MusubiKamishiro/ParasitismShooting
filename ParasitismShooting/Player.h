#pragma once
#include "Geometry.h"
//#include "CharacterObject.h"
//#include <memory>
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
//class GamePlayingScene;

class Player// : public CharacterObject
{
	//friend GamePlayingScene;
private:
	// ��ԑJ�ڂ̂��߂̃����o�֐��|�C���^
	void (Player::*updater)(const Peripheral &p);
	void Move(const Peripheral &p);
	void Shot(const Peripheral &p);			// �U��
	void Die(const Peripheral &p);			// �G�@�ɓ������Ď���

	void Draw(Vector2& pos);				// �v���C���[�̕`��

	void DebugDraw();
	
	void NotOutOfRange();

	Vector2 startPos;			// �J�n���W
	Vector2 pos;				// ���ݍ��W
	Vector2 vel;				// �ړ����x
	int moveVel;				// �ړ���
	
	// �ړ��͈͓�
	int up;
	int right;
	int left;
	int down;

	int img;
	
public:
	Player();
	~Player();

	void Update(const Peripheral &p);

	Vector2 GetPos()const;
};

