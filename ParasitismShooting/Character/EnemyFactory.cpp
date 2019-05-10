#include "EnemyFactory.h"
#include "Fish.h"


ELegion & EnemyFactory::GetLegion()
{
	return legion;		// W‡‘Ì‚ð•Ô‚·
}

EnemyFactory::EnemyFactory(const Player& player) : player(player)
{
	originalEnemy["fish"] = new Fish(player);
}


EnemyFactory::~EnemyFactory()
{
}

Enemy * EnemyFactory::Create(const char * enemyname, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed)
{
	if(originalEnemy.find(enemyname) != originalEnemy.end())
	{
		auto enemy = originalEnemy[enemyname]->Clone();
		enemy->pos = pos;
		enemy->movePtn = movePtn;
		enemy->cnt = cnt;
		enemy->wait = wait;
		enemy->HP = hp;
		enemy->SP = sp;
		//enemy->vel = speed;
		legion.push_back(enemy);

		return enemy;
	}

	return nullptr;
}
