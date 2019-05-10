#include "ShotFactory.h"
#include "Shot.h"
#include "ShotNormal.h"
//#include "Class"


Legion& ShotFactory::GetLegion()
{
	return legion;		// �W���̂�Ԃ�
}

ShotFactory::ShotFactory(const Shot& shot) : shot(shot)
{
	//originalShot["name"] = new Class(player);
	originalShot["ShotNormal"] = new ShotNormal(shot);
}


ShotFactory::~ShotFactory()
{
}

Shot * ShotFactory::Create(const char * enemyname, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed)
{
	//if(originalShot.find(enemyname) != originalShot.end())
	//{
	//	auto shot = originalShot[enemyname]->Clone();
	//	shot->pos = pos;
	//	shot->movePtn = movePtn;
	//	shot->cnt = cnt;
	//	shot->wait = wait;
	//	shot->HP = hp;
	//	shot->SP = sp;
	//	//enemy->vel = speed;
	//	legion.push_back(shot);

	//	return shot;
	//}

	return nullptr;
}