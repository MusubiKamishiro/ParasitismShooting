#include "ShotFactory.h"
#include <random>
#include "Shot.h"
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
float ShotGunRange[9] = { 90,80,100,70,110,60,120,50,130 };

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
		if ((shotType == "ShotWeak" && shooter == SHOOTER::PLAYER) || (shotType == "ShotTracking" && shooter == SHOOTER::PLAYER) || (shotType == "ShotNormal" && shooter == SHOOTER::ENEMY))
		{
			level = 1;
		}
		for (int j = 0; j < level; j++)
		{
		auto shot = originalShot[shotType]->Clone();
			if (shotType == "ShotNormal")
			{
				shot->pos = { pos.x - 10 + NormalPosPtnX[j],pos.y};
				shot->shotst.angle = SetAngle(shotType, pos, shooter);
			}
			else if (shotType == "ShotRadiation")
			{
				shot->pos = pos;
				shot->shotst.angle = M_PI_2 / level /*(level / 4)*/  * j;/*(SetAngle(shotType, pos, shooter) + M_PI_2 * j);*/
			}
			else if (shotType == "ShotRandom")
			{
				std::random_device rd;
				std::mt19937 mt(rd());
				std::uniform_int_distribution<int> rand(1, 10);
				shot->pos = { pos.x - (float)(rand(mt) * M_PI * 2) + 10,pos.y - 30 };
				shot->shotst.angle = SetAngle(shotType, pos, shooter);
			}
			else if (shotType == "ShotShotgun")
			{
				shot->pos = pos;
				if (shooter == SHOOTER::ENEMY)
				{
					shot->shotst.angle = cos(360/level) * j;
				}
				else
				{
					shot->shotst.angle = -(ShotGunRange[j] / 180) * M_PI;
				}
			}
			else if (shotType == "ShotTracking")
			{
				shot->pos = pos;
				shot->shotst.angle = SetAngle(shotType, pos, shooter);
			}
			else if (shotType == "ShotWeak")
			{
				shot->pos = pos;
				shot->shotst.angle = SetAngle(shotType, pos, shooter);
			}
			shot->shotst.shotType = shotType;
			shot->shotst.cpos = pos;
			shot->shotst.speed = Speed;
			shot->shotst.movePtn = movePtn;
			shot->shotst.level = level;
			shot->shotst.shooter = shooter;
			legion.push_back(shot);

			if (j == level)
			{
				return shot;
			}
		}
	}

	return nullptr;
}


double ShotFactory::SetAngle(std::string shotType, Vector2f pos, int shooter)
{
	if (shooter == SHOOTER::ENEMY)
	{
		Vector2f pPos = player.GetPos();
		return atan2(pPos.y - pos.y, pPos.x - pos.x);
	}
	else if(shooter == SHOOTER::PLAYER)
	{
		return -M_PI_2;
	}
}
