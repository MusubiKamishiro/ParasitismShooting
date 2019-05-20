#include "Enemy.h"



Enemy::Enemy(const Player& player)
{
	scoreFlag = false;
}


Enemy::~Enemy()
{
}

void Enemy::ShotStop()
{
	charaData.ShotReady = false;
}

bool Enemy::GetShotReady() const
{
	return charaData.ShotReady;
}

unsigned int Enemy::GetScore() const
{
	return score;
}
