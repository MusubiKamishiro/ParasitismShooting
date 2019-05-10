#include "ShotFactory.h"
//#include "Class"


Legion& ShotFactory::GetLegion()
{
	return legion;		// W‡‘Ì‚ð•Ô‚·
}

ShotFactory::ShotFactory(const Player& player) : player(player)
{
	//originalShot["name"] = new Class(player);
}


ShotFactory::~ShotFactory()
{
}

Shot * ShotFactory::Create(const char * enemyname, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed)
{
	if(originalShot.find(enemyname) != originalShot.end())
	{
		auto shot = originalShot[enemyname]->Clone();
		shot->pos = pos;
		shot->movePtn = movePtn;
		shot->cnt = cnt;
		shot->wait = wait;
		shot->HP = hp;
		shot->SP = sp;
		//enemy->vel = speed;
		legion.push_back(shot);

		return shot;
	}

	return nullptr;
}
