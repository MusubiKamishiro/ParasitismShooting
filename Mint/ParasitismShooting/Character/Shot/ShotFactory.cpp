#include "ShotFactory.h"
#include <random>
#include "Shot.h"
#include "../Player.h"
#include "../Enemy.h"

#include "../../GameScreen.h"
#include "ShotNormal.h"
#include "ShotRadiation.h"
#include "ShotRandom.h"
#include "ShotShotgun.h"
#include "ShotTracking.h"


int NormalPosPtnX[4] = { -10, 10,-30, 30 };
int NormalPosPtnY[4] = { -30,-30,-10,-10 };

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

ShotFactory::ShotFactory(const Player& player/*, const Enemy& enemy*/) : player(player)
{
	GameScreen gscreen;
	Vector2 screenSize = gscreen.GetGSSize();

	up = 0;
	right = screenSize.x + gscreen.outscreen;
	left = 0;
	down = screenSize.y + gscreen.outscreen;

	originalShot["ShotNormal"] = new ShotNormal(player);
	originalShot["ShotRadiation"] = new ShotRadiation(player);
	originalShot["ShotRandom"] = new ShotRandom(player);
	originalShot["ShotShotgun"] = new ShotShotgun(player);
	originalShot["ShotTracking"] = new ShotTracking(player);

}


ShotFactory::~ShotFactory()
{
}

Shot * ShotFactory::Create(std::string shotType, Vector2f pos, int Speed, int movePtn, int level, int shooter)
{
	if (originalShot.find(shotType) != originalShot.end())
	{
		if (shotType == "ShotNormal")
		{
			level = 1;
		}
		for (int j = 0; j < level; j++)
		{
		auto shot = originalShot[shotType]->Clone();
			if (shotType == "ShotNormal")
			{
				//shot->pos = pos;

				shot->pos = { pos.x - 10 + NormalPosPtnX[j],pos.y};
				shot->shotst.angle = SetAngle(pos, shooter);
			}
			else if (shotType == "ShotRadiation")
			{
				shot->pos = pos;

				shot->shotst.angle = (SetAngle(pos, shooter) + M_PI_2 * j);
			}
			else if (shotType == "ShotRandom")
			{
				std::random_device rd;
				std::mt19937 mt(rd());

				std::uniform_int_distribution<int> rand(1, 10);
				shot->pos = { pos.x - (float)(rand(mt) * M_PI * 2) + 10,pos.y - 30 };
				shot->shotst.angle = SetAngle(pos, shooter);
			}
			else if (shotType == "ShotShotgun")
			{
				shot->pos = pos;
				shot->shotst.angle = ((SetAngle(pos, shooter)  * j));
			}
			else if (shotType == "ShotTracking")
			{

				shot->pos = pos;

				shot->shotst.angle = SetAngle(pos, shooter);
			}
			shot->shotst.cpos = pos;
			shot->shotst.shotType = shotType;
			shot->shotst.speed = Speed;
			shot->shotst.level = level;
			shot->shotst.shooter = shooter;
			shot->cnt = 0;
			legion.push_back(shot);

			if (j == level)
			{
				return shot;
			}
		}
	}

	return nullptr;
}

double ShotFactory::SetAngle(Vector2f pos, int shooter)
{
	if (shooter == SHOOTER::ENEMY)
	{
		Vector2f pPos = player.GetPos();
		return atan2(pPos.y - pos.y, pPos.x - pos.x);
	}
	else
	{
		return -M_PI_2;
	}
}
