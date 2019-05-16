#include "EnemyActionPattern.h"
#include "Shot/ShotFactory.h"
#include "Shot/Shot.h"
#include "Player.h"
#include <math.h>

void EnemyActionPattern::UpDown(Vector2f &pos, float speed, int cnt, int wait)
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

void EnemyActionPattern::LeftRight(Vector2f &pos, float speed, int cnt, int wait)
{
	if (cnt < wait / 4)
	{
		pos.x += speed;
	}
	
	if (cnt > wait)
	{
		pos.x -= speed;
	}

}

void EnemyActionPattern::Rush(Vector2f &pos, float speed, int cnt, int wait)
{
}

void EnemyActionPattern::Wavy(Vector2f &pos, float speed, int cnt, int wait)
{
	if ((cnt / 30) % 2 == 0)
	{
		pos.x += speed / 4;
		pos.y += 2 * pow(x, 2);
	}
	else
	{
		pos.x += speed / 4;
		pos.y -= 2 * pow(x, 2);
	}
}

void EnemyActionPattern::Stun(Vector2f &pos, float speed)
{
	pos.y += speed / 2;
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

void EnemyActionPattern::Update(int movePtn, Vector2f & pos, float speed, int cnt, int wait, int shotCnt, int charSP, bool& ShotReady)
{
	if (cnt == shotCnt)
	{
		ShotReady = true;
	}

	if (charSP > 0)
	{
		(this->*movementPtn[movePtn])(pos, speed, cnt, wait);
	}
	else
	{
		Stun(pos, speed);
	}
}
