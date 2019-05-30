#include "EnemyActionPattern.h"
#include "Shot/ShotFactory.h"
#include "Shot/Shot.h"
#include "Player.h"
#include <math.h>

void EnemyActionPattern::UpDown(Vector2f &pos, float moveVel, int cnt, int wait)
{
	if (cnt < wait / 4)
	{
		pos.y += moveVel;
	}

	if (cnt > wait)
	{
		pos.y -= moveVel;
	}
}

void EnemyActionPattern::LeftRight(Vector2f &pos, float moveVel, int cnt, int wait)
{
	if (cnt < wait / 4)
	{
		pos.x += moveVel;
	}

	if (cnt > wait)
	{
		pos.x -= moveVel;
	}

}

void EnemyActionPattern::Rush(Vector2f &pos, float moveVel, int cnt, int wait)
{
}

void EnemyActionPattern::Wavy(Vector2f &pos, float moveVel, int cnt, int wait)
{
	if ((cnt / 30) % 2 == 0)
	{
		pos.x += moveVel / 4;
		pos.y += 2 * pow(x, 2);
	}
	else
	{
		pos.x += moveVel / 4;
		pos.y -= 2 * pow(x, 2);
	}
}

void EnemyActionPattern::Stun(Vector2f &pos, float moveVel)
{
	pos.y += moveVel / 2;
}

EnemyActionPattern::EnemyActionPattern()
{
	movementPtn[MovementPTN::UpDown] = &EnemyActionPattern::UpDown;
	movementPtn[MovementPTN::LeftRight] = &EnemyActionPattern::LeftRight;
	movementPtn[MovementPTN::Rush] = &EnemyActionPattern::Rush;
	movementPtn[MovementPTN::Wavy] = &EnemyActionPattern::Wavy;
}

EnemyActionPattern::~EnemyActionPattern()
{
}

void EnemyActionPattern::Update(int movePtn, Vector2f & pos, float moveVel, int cnt, int wait, int shotCnt, int charSP, bool& ShotReady)
{
	if (cnt == shotCnt)
	//if ((cnt % 60) == 1)
	{
		ShotReady = true;
	}
	if (charSP > 0)
	{
		(this->*movementPtn[movePtn])(pos, moveVel, cnt, wait);
	}
	else
	{
		Stun(pos, moveVel);
	}
}
