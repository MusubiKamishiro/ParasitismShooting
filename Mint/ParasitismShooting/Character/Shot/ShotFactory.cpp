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

Shot * ShotFactory::Create(const char * shotname, Vector2f pos, float angle, int Speed, int movePtn, int level, int shotPtn, int shooter)
{
	if (originalShot.find(shotname) != originalShot.end())
	{
		for (int j = 0; j < level; j++)
		{
		auto shot = originalShot[shotname]->Clone();
			if (shotname == "ShotNormal")
			{
				//shot->pos = pos;

				shot->pos = { pos.x - 10 + NormalPosPtnX[j],pos.y + NormalPosPtnY[j] };
				shot->shotst.angle = -M_PI_2;
			}
			else if (shotname == "ShotRadiation")
			{
				shot->pos = pos;

				shot->shotst.angle = -(angle + M_PI_2 / (level / 4)  * j);
			}
			else if (shotname == "ShotRandom")
			{
				std::random_device rd;
				std::mt19937 mt(rd());

				std::uniform_int_distribution<int> rand(1, 10);
				shot->pos = { pos.x - (float)(rand(mt) * M_PI * 2) + 10,pos.y - 30 };
				shot->shotst.angle = angle;
			}
			else if (shotname == "ShotShotgun")
			{
				shot->pos = pos;
				shot->shotst.angle = -(((angle + (M_PI / level))  * j) + M_PI / 6);
			}
			else if (shotname == "ShotTracking")
			{
				for (int j = 0; j < level; j++)
				{
					shot->pos = { pos.x + 20 * j,pos.y };
				}
				shot->shotst.angle = angle;
			}
			shot->shotst.cpos = pos;
			shot->shotst.speed = Speed;
			shot->shotst.movePtn = movePtn;
			shot->shotst.level = level;
			shot->shotst.shotPtn = shotPtn;
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
