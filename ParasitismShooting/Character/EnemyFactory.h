#pragma once
#include "../Geometry.h"
#include <list>
#include <map>

class Enemy;
class Player;

typedef std::list<Enemy*> ELegion;	// “G‚ÌW‡‘Ì‚ÌŒ^

class EnemyFactory
{
private:
	const Player& player;
	
	std::map<std::string, Enemy*> originalEnemy;	// “G‚ÌŒ³‚Æ‚È‚émap‚Ìì¬
	ELegion legion;

public:
	EnemyFactory(const Player& player);
	~EnemyFactory();

	// “G‚ğì‚é
	// enemyname...“G‚Ì–¼‘O
	Enemy* Create(const char * enemyname, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed);
	
	// “G‚ÌW‡‘Ì‚ğ•Ô‚·
	ELegion& GetLegion();
	// ƒ_ƒ[ƒW’e‚É“–‚½‚Á‚½‚ğÁ‚·
	void EnemyDelete();
};

