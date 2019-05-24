#include "ShotFactory.h"
#include <random>
#include "../Player.h"
#include "../EnemyFactory.h"

#include "../../GameScreen.h"
#include "ShotNormal.h"
#include "ShotRadiation.h"
#include "ShotRandom.h"
#include "ShotShotgun.h"
#include "ShotTracking.h"
#include "ShotWeak.h"

int NormalPosPtnX[5] = { 0,-5, 5,-10, 10 };

SLegion& ShotFactory::GetLegion()
{
	return legion;		// èWçáëÃÇï‘Ç∑
}

void ShotFactory::ShotDelete()
{
	for (int i = 0; i < legion.size(); ++i)
	{
		auto shot = *std::next(legion.begin(), i);
		if (!shot->GetLifeFlag())
		{
			legion.erase(std::next(legion.begin(), i));
			--i;
		}
	}
}

void ShotFactory::OutofScreen(void)
{
	for(auto &shot :legion)
	{
		if (shot->pos.x < left - shot->rect.Width() / 2 || shot->pos.x > right + shot->rect.Width() / 2 ||
			shot->pos.y < up - shot->rect.Height() / 2 || shot->pos.y > down + shot->rect.Height() / 2)
		{
			shot->lifeFlag = false;
		}
	}
}

ShotFactory::ShotFactory(const Player& player, const EnemyFactory& enemyfactory) : player(player), enemyfactory(enemyfactory)
{
	GameScreen gscreen;
	Vector2 screenSize = gscreen.GetGSSize();

	up = 0;
	right = screenSize.x + gscreen.outscreen;
	left = 0;
	down = screenSize.y + gscreen.outscreen;

	originalShot["ShotNormal"] = new ShotNormal(player, enemyfactory);
	originalShot["ShotRadiation"] = new ShotRadiation(player, enemyfactory);
	originalShot["ShotRandom"] = new ShotRandom(player, enemyfactory);
	originalShot["ShotShotgun"] = new ShotShotgun(player, enemyfactory);
	originalShot["ShotTracking"] = new ShotTracking(player, enemyfactory);
	originalShot["ShotWeak"] = new ShotWeak(player, enemyfactory);
}


ShotFactory::~ShotFactory()
{
}

Shot * ShotFactory::Create(std::string shotType, Vector2f pos, int Speed, int movePtn, int level, int shooter)
{
	if (originalShot.find(shotType) != originalShot.end())
	{
		if ((shotType == "ShotWeak" && shooter == SHOOTER::PLAYER) || (shotType == "ShotNormal" && shooter == SHOOTER::ENEMY))
		{
			level = 1;
		}
		for (int j = 0; j < level; j++)
		{
			if (shotType == "ShotRadiation")
			{
				break;
			}
			auto shot = originalShot[shotType]->Clone();
			shot->pos = pos;
			shot->shotst.shotType = shotType;
			shot->shotst.cpos = pos;
			shot->shotst.speed = Speed;
			shot->shotst.movePtn = movePtn;
			shot->shotst.level = level;
			shot->shotst.shooter = shooter;
			shot->shotst.time = 0;
			shot->shotst.angle = SetAngle(shot->shotst.shotType, shot->pos, shot->shotst.shooter, j, level);
			legion.push_back(shot);
		}
	}
	return nullptr;
}

double ShotFactory::SetAngle(std::string shotType, Vector2f pos, int shooter, int cnt, int level)
{
	angle = -M_PI_2;
	if (shotType == "ShotNormal")
	{
		if (shooter == SHOOTER::ENEMY)
		{
			Vector2f pPos = player.GetPos();
			return atan2(pPos.y - pos.y, pPos.x - pos.x);
		}
		else if (shooter == SHOOTER::PLAYER)
		{
			return -M_PI_2;
		}
	}
	else if (shotType == "ShotRadiation")
	{
		Vector2f pPos = player.GetPos();
		angle = atan2(pPos.y - pos.y, pPos.x - pos.x);
		angle += 360 / level * cnt;
		return angle;

	}
	else if (shotType == "ShotShotgun")
	{
		if (shooter == SHOOTER::ENEMY)
		{
			Vector2f pPos = player.GetPos();
			angle = atan2(pPos.y - pos.y, pPos.x - pos.x);
			if (level / 2 > cnt)
			{
				angle -= M_PI * (10.0f  * (cnt + 1) / 180.0f);
			}
			else if (level / 2 < cnt)
			{
				angle += M_PI * (10.0f * (cnt - (level / 2)) / 180.0f);
			}
			return angle;
		}
		else
		{
			if (level / 2 > cnt)
			{
				angle -= M_PI * (10.0f  * (cnt + 1) / 180.0f);

			}
			else if (level / 2 < cnt)
			{
				angle += M_PI * (10.0f * (cnt - (level / 2)) / 180.0f);
			}
			return  angle;
		}
	}
	else if (shotType == "ShotTracking")
	{
		if (shooter == SHOOTER::ENEMY)
		{
			return M_PI_2;
		}
		else if (shooter == SHOOTER::PLAYER)
		{
			if (level / 2 > cnt)
			{
				angle -= M_PI * (10.0f  * (cnt + 1) / 180.0f);

			}
			else if (level / 2 < cnt)
			{
				angle += M_PI * (10.0f * (cnt - (level / 2)) / 180.0f);
			}
			return  angle;
		}
	}
	else if (shotType == "ShotWeak")
	{
		return -M_PI_2;
	}
}
