#include "ShotFactory.h"
#include "Shot.h"
#include "../Player.h"
#include "../Enemy.h"
#include "ShotNormal.h"
//#include "Class"


SLegion& ShotFactory::GetLegion()
{
	return legion;		// �W���̂�Ԃ�
}

ShotFactory::ShotFactory(const Player& player/*, const Enemy& enemy*/) : player(player)
{
	//originalShot["name"] = new Class(player);
	originalShot["ShotNormal"] = new ShotNormal(player);
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
