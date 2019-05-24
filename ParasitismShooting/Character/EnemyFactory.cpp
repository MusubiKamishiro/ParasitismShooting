#include "EnemyFactory.h"
#include "Fish.h"
#include "../GameScreen.h"


ELegion & EnemyFactory::GetLegion()
{
	return legion;		// W‡‘Ì‚ð•Ô‚·
}

Vector2f  EnemyFactory::GetLegionBeginCharPos() const
{
	if (legion.size() != 0)
	{
		auto itr = *legion.begin();
		return itr->GetPos();
	}
}

void EnemyFactory::EnemyDelete()
{
	for (int i = 0; i < legion.size(); ++i)
	{
		auto enemy = *std::next(legion.begin(), i);
		if (!enemy->GetLifeFlag())
		{
			legion.erase(std::next(legion.begin(), i));
			--i;
		}
	}
}

void EnemyFactory::OutofScreen()
{
	for (auto &enemy : legion)
	{
		if (enemy->pos.x < left - enemy->rect.Width() / 2 || enemy->pos.x > right + enemy->rect.Width() / 2 ||
			enemy->pos.y < up - enemy->rect.Height() / 2 || enemy->pos.y > down + enemy->rect.Height() / 2)
		{
			enemy->lifeFlag = false;
		}
	}
}

EnemyFactory::EnemyFactory(const Player& player) : player(player)
{
	GameScreen gscreen;
	Vector2 screenSize = gscreen.GetGSSize();

	up = 0;
	right = screenSize.x + gscreen.outscreen;
	left = 0;
	down = screenSize.y + gscreen.outscreen;

	originalEnemy["fish"] = new Fish(player);
}


EnemyFactory::~EnemyFactory()
{
}

Enemy * EnemyFactory::Create(const char * enemyname, const char * shotType, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed, int shotCnt)
{
	if(originalEnemy.find(enemyname) != originalEnemy.end())
	{
		auto enemy = originalEnemy[enemyname]->Clone();
		enemy->charaData.shotType = shotType;
		enemy->pos = pos;
		enemy->movePtn = movePtn;
		enemy->cnt = cnt;
		enemy->wait = wait;
		enemy->charaData.HP = hp;
		enemy->charaData.SP = sp;
		enemy->charaData.moveVel = speed;
		enemy->shotCnt = shotCnt;
		legion.push_back(enemy);

		return enemy;
	}

	return nullptr;
}
