#include "ShotFactory.h"
#include <random>
#include "Shot.h"
#include "../Player.h"
#include "../Enemy.h"
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

ShotFactory::ShotFactory(const Player& player/*, const Enemy& enemy*/) : player(player)
{
	//originalShot["name"] = new Class(player);
	originalShot["ShotNormal"] = new ShotNormal(player);
	originalShot["ShotRadiation"] = new ShotRadiation(player);
	originalShot["ShotRandom"] = new ShotRandom(player);
	originalShot["ShotShotgun"] = new ShotShotgun(player);
	originalShot["ShotTracking"] = new ShotTracking(player);

}


ShotFactory::~ShotFactory()
{
}

Shot * ShotFactory::Create(const char * shotname,Vector2f pos, float angle, int Speed, int movePtn, int level, int shotPtn, int shooter)
{
	if(originalShot.find(shotname) != originalShot.end())
	{
		auto shot = originalShot[shotname]->Clone();
		if (shotname == "ShotNormal")
		{
			shot->pos = pos;
			/*shot->pos = { pos.x - 10 + NormalPosPtnX[cnt],pos.y + NormalPosPtnY[cnt] };*/
			shot->angle = -M_PI_2;
		/*	cnt++;
			if (cnt == level)
			{
				cnt = 0;
			}*/
		}
		else if (shotname == "ShotRadiation")
		{
			shot->pos = pos;

			shot->angle = -(angle + M_PI_2 / (level / 4)  * cnt);
			cnt++;
			if (cnt == level)
			{
				cnt = 0;
			}
		}
		else if (shotname == "ShotRandom")
		{
			std::random_device rd;
			std::mt19937 mt(rd());

			std::uniform_int_distribution<int> rand(1, 10);
			shot->pos = { pos.x - (float)(rand(mt) * M_PI * 2) + 10,pos.y - 30 };
			shot->angle = angle;
		}
		else if (shotname == "ShotShotgun")
		{
			shot->pos = pos;
			
			shot->angle = -(((angle + (M_PI / level))  * cnt) + M_PI / 6);
			cnt++;
			if (cnt == level)
			{
				cnt = 0;
			}
		}
		else if (shotname == "ShotTracking")
		{
			for (int j = 0; j < level; j++)
			{
				shot->pos = { pos.x + 20 * j,pos.y };
			}
			shot->angle = angle;
		}
		shot->cneterPos = pos;
		shot->Speed = Speed;
		shot->movePtn = movePtn;
		shot->level = level;
		shot->shotPtn = shotPtn;
		shot->shooter = shooter;
		legion.push_back(shot);

		return shot;
	}

	return nullptr;
}
