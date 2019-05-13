#include "EnemyActionPattern.h"
#include "Shot/ShotFactory.h"
#include "Shot/Shot.h"
#include "Player.h"

void EnemyActionPattern::ActPattern0(Vector2f &pos, float speed, int cnt, int wait)
{
	if (cnt < wait / 2)
	{
		pos.y += speed;
	}
	if (cnt > 120 + wait)
	{
		pos.y -= speed;
	}
}

void EnemyActionPattern::ActPattern1(void)
{
}

void EnemyActionPattern::ActPattern2(void)
{
}

void EnemyActionPattern::ActPattern3(void)
{
}

void EnemyActionPattern::ActPattern4(Vector2f &pos, float speed)
{
	pos.y += speed;
}

EnemyActionPattern::EnemyActionPattern()
{
}

EnemyActionPattern::~EnemyActionPattern()
{
}