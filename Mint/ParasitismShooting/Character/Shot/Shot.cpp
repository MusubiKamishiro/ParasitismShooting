#include "Shot.h"
#include "../Player.h"
#include "../EnemyFactory.h"



Shot::Shot(const Player & player, const EnemyFactory& enemyfactory/*, const Enemy& enemy*/) :player(player), enemyfactory(enemyfactory)
{
}

Shot::~Shot()
{
}

float Shot::SetTracking(std::string shotType, Vector2f pos, int shooter, float oldangle)
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
	return 0.0f;
}

float Shot::GetAtan2(int shooter, float oldangle)
{
	if (shooter == SHOOTER::ENEMY)
	{
		Vector2f pPos = player.GetPos();
		if (pPos != Vector2f(0.0f, 0.0f))
		{
			return atan2(pPos.y - pos.y, pPos.x - pos.x);
		}
	}
	else if (shooter == SHOOTER::PLAYER)
	{
		Vector2f ePos = enemyfactory.GetLegionBeginCharPos();
		if (ePos != Vector2f(0.0f, 0.0f))
		{
			return atan2(ePos.y - pos.y, ePos.x - pos.x);
		}
	}
	return oldangle;
}



int Shot::GetShooter()const
{
	return shotst.shooter;
}

std::string Shot::GetShotName() const
{
	return shotst.shotType;
}
