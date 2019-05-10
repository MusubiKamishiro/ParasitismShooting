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
	int cnt = 0;
	const Player& player;
	
	std::map<std::string, Shot*> originalShot;	// ’e‚ÌŒ³‚Æ‚È‚émap‚Ìì¬
	SLegion legion;

public:
	ShotFactory(const Player& player/*, const Enemy& enemy*/);
	~ShotFactory();

	// ’e‚ğì‚é
	// enemyname...’e‚Ì–¼‘O
	Shot* Create(const char * shotname,Vector2f pos, float angle, int Speed, int movePtn, int level, int shotPtn, int shooter);
	
	// ’e‚ÌW‡‘Ì‚ğ•Ô‚·
	SLegion& GetLegion();
};

