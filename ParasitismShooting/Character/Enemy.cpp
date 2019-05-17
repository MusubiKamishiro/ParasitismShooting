#include "Enemy.h"



Enemy::Enemy(const Player& player)
{
	scoreFlag = false;
}


Enemy::~Enemy()
{
}

bool Enemy::GetShotReady() const
{
	return charaData.ShotReady;
}

unsigned int Enemy::GetScore() const
{
	return score;
}
