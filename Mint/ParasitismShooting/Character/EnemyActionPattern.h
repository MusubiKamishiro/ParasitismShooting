#pragma once
#include <iostream>
#include "../Geometry.h"
class Player;

//typedef void(EnemyActionPattern::*movePtn[])(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag);

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
	void Update(int movePtn, Vector2f &pos, Vector2f Speed, int cnt, int wait, bool lifeFlag);
private:
	void UpDown(Vector2f &pos, Vector2f speed, int cnt, int wait, bool lifeFlag);		// 上下移動
	void LeftRight(Vector2f &pos, Vector2f speed, int cnt, int wait, bool lifeFlag);		// 左右に履ける
	void Rush(Vector2f &pos, Vector2f speed, int cnt, int wait, bool lifeFlag);		// 自機に特攻を仕掛ける
	void Wavy(Vector2f &pos, Vector2f speed, int cnt, int wait, bool lifeFlag);		// 波状移動
	void Stun(Vector2f &pos, Vector2f speed);		// 気絶状態

	void(EnemyActionPattern::*movementPtn[MOVEMENT_PTN_MAX])(Vector2f &pos, Vector2f vel, int cnt, int wait, bool lifeFlag)/* = { &EnemyActionPattern::UpDown,&EnemyActionPattern::LeftRight }*/;
};
 