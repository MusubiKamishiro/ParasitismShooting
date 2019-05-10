#pragma once
#include "../../Geometry.h"
#include <list>
#include <map>

class Shot;
class Player;
class Enemy;

typedef std::list<Shot*> SLegion;	// ’e‚ÌW‡‘Ì‚ÌŒ^

class ShotFactory
{
private:
	const Player& player;
	
	std::map<std::string, Shot*> originalShot;	// ’e‚ÌŒ³‚Æ‚È‚émap‚Ìì¬
	SLegion legion;

public:
	ShotFactory(const Player& player/*, const Enemy& enemy*/);
	~ShotFactory();

	// ’e‚ğì‚é
	// enemyname...’e‚Ì–¼‘O
	Shot* Create(const char* enemyname, Vector2f pos, int movePtn, int cnt, int wait, int hp, int sp, float speed);
	
	// ’e‚ÌW‡‘Ì‚ğ•Ô‚·
	SLegion& GetLegion();
};

