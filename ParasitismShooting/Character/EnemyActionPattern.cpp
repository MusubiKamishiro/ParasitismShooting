#include "EnemyActionPattern.h"

void EnemyActionPattern::ActPattern0(Vector2f &pos, float speed, int cnt, int wait)
{
	if (cnt < 60)
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

EnemyActionPattern::EnemyActionPattern()
{
}

EnemyActionPattern::~EnemyActionPattern()
{
}