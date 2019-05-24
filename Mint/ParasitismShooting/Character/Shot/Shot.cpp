#include "Shot.h"
#include "../Player.h"
#include "../EnemyFactory.h"



Shot::Shot(const Player & player, const EnemyFactory& enemyfactory/*, const Enemy& enemy*/):player(player),enemyfactory(enemyfactory)
{
}

Shot::~Shot()
{
}

double Shot::SetTracking(std::string shotType, Vector2f pos, int shooter, double oldangle)
{
	Vector2f pPos = player.GetPos();
	Vector2f ePos = enemyfactory.GetLegionBeginCharPos();
	if (shooter == SHOOTER::ENEMY)
	{
		if (pos.y > pPos.y || (pPos.y - pos.y < 40) || (pos.x - pPos.x < 60 && pos.x - pPos.x > -60))
		{
			return oldangle;
		}
		return atan2(pPos.y - pos.y, pPos.x - pos.x);
	}
	else if (shooter == SHOOTER::PLAYER)
	{
		if (ePos.x > 0.0f && ePos.y > 0.0f)
		{
			if (pos.y < ePos.y || (pPos.y - pos.y < 40))
			{
				return oldangle;
			}
			return atan2(ePos.y - pos.y, ePos.x - pos.x);
		}
		return oldangle;
	}
}

int Shot::GetShooter()const
{
	return shotst.shooter;
}

std::string Shot::GetShotName() const
{
	return shotst.shotType;
}
