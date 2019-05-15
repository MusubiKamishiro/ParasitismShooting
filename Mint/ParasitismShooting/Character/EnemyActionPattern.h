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
	void UpDown(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag, bool& ShotReady);		// 上下移動
	void LeftRight(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag, bool& ShotReady);		// 左右に履ける
	void Rush(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag, bool& ShotReady);		// 自機に特攻を仕掛ける
	void Wavy(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag, bool& ShotReady);		// 波状移動
	void Stun(Vector2f &pos, float speed);		// 気絶状態

	void(EnemyActionPattern::*movementPtn[MOVEMENT_PTN_MAX])(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag, bool& ShotReady)/* = { &EnemyActionPattern::UpDown,&EnemyActionPattern::LeftRight }*/;
};
