#pragma once
#include "../../Geometry.h"
#include <list>
#include <map>

class Shot;
class Player;

typedef std::list<Shot*> Legion;	// ’e‚ÌW‡‘Ì‚ÌŒ^

class ShotFactory
{
private:
	const Player& player;
	
	std::map<std::string, Shot*> originalShot;	// ’e‚ÌŒ³‚Æ‚È‚émap‚Ìì¬
	Legion legion;

public:
	ShotFactory(const Player& player);
	~ShotFactory();

	// ’e‚ğì‚é
	// enemyname...’e‚Ì–¼‘O
	Shot* Create(const char* enemyname, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed);
	
	// ’e‚ÌW‡‘Ì‚ğ•Ô‚·
	Legion& GetLegion();
};

