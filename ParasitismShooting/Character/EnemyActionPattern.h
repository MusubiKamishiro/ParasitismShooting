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
	void Update(int movePtn, Vector2f &pos, float Speed, int cnt, int wait, bool lifeFlag);
private:
	void UpDown(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag);		// ã‰ºˆÚ“®
	void LeftRight(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag);		// ¶‰E‚É—š‚¯‚é
	void Rush(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag);		// ©‹@‚É“ÁU‚ğdŠ|‚¯‚é
	void Wavy(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag);		// ”góˆÚ“®
	void Stun(Vector2f &pos, float speed);		// ‹Câó‘Ô

	void(EnemyActionPattern::*movementPtn[MOVEMENT_PTN_MAX])(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag)/* = { &EnemyActionPattern::UpDown,&EnemyActionPattern::LeftRight }*/;
};
