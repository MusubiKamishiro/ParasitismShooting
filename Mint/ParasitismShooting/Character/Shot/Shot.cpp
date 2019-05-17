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
	return shotst.shooter;
}

std::string Shot::GetShotName() const
{
	return shotst.shotname;
}



//double Shot::ShotAngle(Vector2f pos)
//{
//	//Vector2f pPos = player->GetPos();
//	//return atan2(pPos.y - pos.y,pPos.x - pos.x);
//	return atan2(b - pos.y, a - pos.x);
//}