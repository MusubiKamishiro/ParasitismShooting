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
	charaData.shotReady = false;
}

bool Enemy::GetShotReady() const
{
	return charaData.shotReady;
}

unsigned int Enemy::GetScore() const
{
	return score;
}
