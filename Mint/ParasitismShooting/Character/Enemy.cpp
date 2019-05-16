#include "Enemy.h"



Enemy::Enemy(const Player& player)
{
}


Enemy::~Enemy()
{
}

bool Enemy::GetShotReady() const
{
	return charaData.ShotReady;
}
