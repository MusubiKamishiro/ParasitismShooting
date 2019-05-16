#include "Shot.h"
#include "../Player.h"
#include "../Enemy.h"



Shot::Shot(const Player & player/*, const Enemy& enemy*/)
{
}

Shot::~Shot()
{
}

int Shot::GetShooter()const
{
	return shooter;
}
