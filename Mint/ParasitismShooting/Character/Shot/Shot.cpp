#include "Shot.h"
#include "../Player.h"
//#include "../Enemy.h"
#include "../EnemyFactory.h"



Shot::Shot(const Player & player, const EnemyFactory& enemyfactory/*, const Enemy& enemy*/)
{
}

Shot::~Shot()
{
}

int Shot::GetShooter()const
{
	return shotst.shooter;
}

std::string Shot::GetShotName() const
{
	return shotst.shotType;
}
