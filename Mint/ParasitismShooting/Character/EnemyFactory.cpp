#include "EnemyFactory.h"
#include "Fish.h"


Legion & EnemyFactory::GetLegion()
{
	return legion;		// W‡‘Ì‚ğ•Ô‚·
}

EnemyFactory::EnemyFactory(const Player& player) : player(player)
{
	originalEnemy["fish"] = new Fish(player);
}


EnemyFactory::~EnemyFactory()
{
}

Enemy * EnemyFactory::Create(const char * enemyname, Vector2f pos,int movePtn, int cnt, int wait)
{
	if(originalEnemy.find(enemyname) != originalEnemy.end())
	{
		auto enemy = originalEnemy[enemyname]->Clone();
		enemy->pos = pos;
		enemy->movePtn = movePtn;
		enemy->cnt = cnt;
		enemy->wait = wait;
		legion.push_back(enemy);
		enemy->flag = true;

		return enemy;
	}

	return nullptr;
}
