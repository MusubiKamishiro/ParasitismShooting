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

	int up;
	int right;
	int left;
	int down;
public:
	ShotFactory(const Player& player/*, const Enemy& enemy*/);
	~ShotFactory();

	// ’e‚ğì‚é
	// enemyname...’e‚Ì–¼‘O
	Shot* Create(const char * shotname,Vector2f pos, int Speed, int movePtn, int level, int shooter);
	
	// ’e‚ÌW‡‘Ì‚ğ•Ô‚·
	SLegion& GetLegion();
	// ‘¼‚Ì‚à‚Ì‚É“–‚½‚Á‚½’e‚ğÁ‚·
	void ShotDelete();
	void OutofScreen(void);

	double SetAngle(Vector2f pos, int shooter);
};

