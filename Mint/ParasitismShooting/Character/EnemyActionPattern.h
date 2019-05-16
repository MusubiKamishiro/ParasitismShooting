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
	void Update(int movePtn, Vector2f & pos, float speed, int cnt, int wait, int shotCnt, bool lifeFlag, bool& ShotReady);
private:
	void UpDown(Vector2f &pos, float speed, int cnt, int wait, int shotCnt, bool lifeFlag, bool& ShotReady);		// è„â∫à⁄ìÆ
	void LeftRight(Vector2f &pos, float speed, int cnt, int wait, int shotCnt, bool lifeFlag, bool& ShotReady);		// ç∂âEÇ…óöÇØÇÈ
	void Rush(Vector2f &pos, float speed, int cnt, int wait, int shotCnt, bool lifeFlag, bool& ShotReady);		// é©ã@Ç…ì¡çUÇédä|ÇØÇÈ
	void Wavy(Vector2f &pos, float speed, int cnt, int wait, int shotCnt, bool lifeFlag, bool& ShotReady);		// îgèÛà⁄ìÆ
	void Stun(Vector2f &pos, float speed);		// ãCê‚èÛë‘

	void(EnemyActionPattern::*movementPtn[MOVEMENT_PTN_MAX])(Vector2f &pos, float speed, int cnt, int wait, int shotCnt, bool lifeFlag, bool& ShotReady);

	int x = 1;
};
