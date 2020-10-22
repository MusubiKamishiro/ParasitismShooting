#pragma once
#include <iostream>
#include "../Geometry.h"
class Player;

enum MovementPTN
{
	UpDown,
	LeftRight,
	Rush,
	Wavy,
	Stun,
	FadeOut,
	MOVEMENT_PTN_MAX
};

class EnemyActionPattern
{
public:
	EnemyActionPattern();
	~EnemyActionPattern();
	void Update(int movePtn, Vector2f & pos, float speed, int cnt, int wait, int shotCnt, int charSP, bool& ShotReady);
private:
	void UpDown(Vector2f &pos, float speed, int cnt, int wait);		// ã‰ºˆÚ“®
	void LeftRight(Vector2f &pos, float speed, int cnt, int wait);	// ¶‰E‚É—š‚¯‚é
	void Rush(Vector2f &pos, float speed, int cnt, int wait);		// ©‹@‚É“ÁU‚ğdŠ|‚¯‚é
	void Wavy(Vector2f &pos, float speed, int cnt, int wait);		// ”góˆÚ“®
	void FadeOut(Vector2f &pos, float speed, int cnt, int wait);
	void Stun(Vector2f &pos, float speed);		// ‹Câó‘Ô

	void(EnemyActionPattern::*movementPtn[MOVEMENT_PTN_MAX])(Vector2f &pos, float speed, int cnt, int wait);

	int x = 1;
};
