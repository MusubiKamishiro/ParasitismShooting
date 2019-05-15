#pragma once
#include "../Geometry.h"
#include <memory>
class Player;
class ShotFactory;
class GamePlayingScene;


enum MovementPTN
{
	UpDown,
	LeftRight,
	Rush,
	Wavy,
	Stun,
	MOVEMENT_PTN_MAX
};

class EnemyActionPattern
{
public:
	EnemyActionPattern();
	~EnemyActionPattern();
	void Update(int movePtn, Vector2f &pos, float Speed, int cnt, int wait, bool lifeFlag, bool& ShotReady);
private:
	void UpDown(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag, bool& ShotReady);		// �㉺�ړ�
	void LeftRight(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag, bool& ShotReady);		// ���E�ɗ�����
	void Rush(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag, bool& ShotReady);		// ���@�ɓ��U���d�|����
	void Wavy(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag, bool& ShotReady);		// �g��ړ�
	void Stun(Vector2f &pos, float speed);		// �C����

	void(EnemyActionPattern::*movementPtn[MOVEMENT_PTN_MAX])(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag, bool& ShotReady)/* = { &EnemyActionPattern::UpDown,&EnemyActionPattern::LeftRight }*/;
};
