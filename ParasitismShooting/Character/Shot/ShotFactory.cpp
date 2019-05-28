#include "ShotFactory.h"
#include <random>
#include "../Player.h"
#include "../EnemyFactory.h"

#include "../../GameScreen.h"
#include "Normal.h"
#include "Radiation.h"
#include "Random.h"
#include "Shotgun.h"
#include "Tracking.h"
#include "Weak.h"
#include "CircleCross.h"

int NormalPosPtnX[5] = { 0,-5, 5,-10, 10 };

SLegion& ShotFactory::GetLegion()
{
	return legion;		// èWçáëÃÇï‘Ç∑
}

void ShotFactory::ShotDelete()
{
	for (unsigned int i = 0; i < legion.size(); ++i)
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

	originalShot["Normal"] = new Normal(player, enemyfactory);
	originalShot["Radiation"] = new Radiation(player, enemyfactory);
	originalShot["Random"] = new Random(player, enemyfactory);
	originalShot["Shotgun"] = new Shotgun(player, enemyfactory);
	originalShot["Tracking"] = new Tracking(player, enemyfactory);
	originalShot["Weak"] = new Weak(player, enemyfactory);
	originalShot["CircleCross"] = new CircleCross(player, enemyfactory);
}


ShotFactory::~ShotFactory()
{
}

Shot * ShotFactory::Create(std::string shotType, Vector2f pos, int Speed, int movePtn, int level, int shooter)
{
	if (originalShot.find(shotType) != originalShot.end())
	{
		if ((shotType == "Weak" && shooter == SHOOTER::PLAYER) || (shotType == "Normal" && shooter == SHOOTER::ENEMY))
		{
			level = 1;
		}
		for (int j = 0; j < level; j++)
		{
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

float ShotFactory::SetAngle(std::string shotType, Vector2f pos, int shooter, int cnt, int level)
{
	angle = -(float)M_PI_2;
	if (shotType == "Normal")
	{
		if (shooter == SHOOTER::ENEMY)
		{
			Vector2f pPos = player.GetPos();
			return atan2(pPos.y - pos.y, pPos.x - pos.x);
		}
		else if (shooter == SHOOTER::PLAYER)
		{
			return -(float)M_PI_2;
		}
	}
	else if (shotType == "Radiation")
	{
		if (shooter == SHOOTER::ENEMY)
		{
			angle = (float)M_PI * ((360.0f / level) * (cnt) / 180.0f);
			return angle;
		}
		else if (shooter == SHOOTER::PLAYER)
		{
			angle = (float)M_PI * ((360.0f / level) * (cnt) / 180.0f);
			return angle;
		}

	}
	else if (shotType == "Shotgun")
	{
		if (shooter == SHOOTER::ENEMY)
		{
			Vector2f pPos = player.GetPos();
			angle = atan2(pPos.y - pos.y, pPos.x - pos.x);
			if (level / 2 > cnt)
			{
				angle -= (float)M_PI * (10.0f  * (cnt + 1) / 180.0f);
			}
			else if (level / 2 < cnt)
			{
				angle += (float)M_PI * (10.0f * (cnt - (level / 2)) / 180.0f);
			}
			return angle;
		}
		else
		{
			if (level / 2 > cnt)
			{
				angle -= (float)M_PI * (10.0f  * (cnt + 1) / 180.0f);

			}
			else if (level / 2 < cnt)
			{
				angle += (float)M_PI * (10.0f * (cnt - (level / 2)) / 180.0f);
			}
			return  angle;
		}
	}
	else if (shotType == "Tracking")
	{
		if (shooter == SHOOTER::ENEMY)
		{
			return (float)M_PI_2;
		}
		else if (shooter == SHOOTER::PLAYER)
		{
			if (level / 2 > cnt)
			{
				angle -= (float)M_PI * (10.0f  * (cnt + 1) / 180.0f);

			}
			else if (level / 2 < cnt)
			{
				angle += (float)M_PI * (10.0f * (cnt - (level / 2)) / 180.0f);
			}
			return  angle;
		}
	}
	else if (shotType == "Weak")
	{
		return -(float)M_PI_2;
	}
	return 0.0f;
}
