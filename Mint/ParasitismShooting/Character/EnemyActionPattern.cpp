#include "EnemyActionPattern.h"
#include "Shot/ShotFactory.h"
#include "Shot/Shot.h"
#include "Player.h"

void EnemyActionPattern::UpDown(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag)
{
	if (cnt < wait / 4)
	{
		pos.y += speed;
	}
	if (cnt > wait)
	{
		pos.y -= speed;
	}
}

void EnemyActionPattern::LeftRight(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag)
{
}

void EnemyActionPattern::Rush(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag)
{
}

void EnemyActionPattern::Wavy(Vector2f &pos, float speed, int cnt, int wait, bool lifeFlag)
{
}

void EnemyActionPattern::Stun(Vector2f &pos, float speed)
{
	pos.y += speed;
}

EnemyActionPattern::EnemyActionPattern()
{
	movementPtn[0] = &EnemyActionPattern::UpDown;
	movementPtn[1] = &EnemyActionPattern::LeftRight;
	movementPtn[2] = &EnemyActionPattern::Rush;
	movementPtn[3] = &EnemyActionPattern::Wavy;
}

EnemyActionPattern::~EnemyActionPattern()
{
}

void EnemyActionPattern::Update(int movePtn, Vector2f & pos, float speed, int cnt, int wait, bool lifeFlag)
{
	(this->*movementPtn[movePtn])(pos, speed, cnt, wait, lifeFlag);
}
