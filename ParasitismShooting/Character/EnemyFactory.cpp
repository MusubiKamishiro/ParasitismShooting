#include "EnemyFactory.h"
#include "Fish.h"


Legion & EnemyFactory::GetLegion()
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

Enemy * EnemyFactory::Create(const char * enemyname, Vector2f pos)
{
	if(originalEnemy.find(enemyname) != originalEnemy.end())
	{
		auto enemy = originalEnemy[enemyname]->Clone();
		enemy->pos = pos;
		legion.push_back(enemy);

		return enemy;
	}

	return nullptr;
}
