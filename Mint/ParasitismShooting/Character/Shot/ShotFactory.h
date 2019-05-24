#pragma once
#include "../../Geometry.h"
#include <list>
#include <map>

class Shot;
class Player;
class EnemyFactory;

typedef std::list<Shot*> SLegion;	// ’e‚ÌW‡‘Ì‚ÌŒ^

class ShotFactory
{
private:
	const Player& player;
	const EnemyFactory& enemyfactory;
	
	std::map<std::string, Shot*> originalShot;	// ’e‚ÌŒ³‚Æ‚È‚émap‚Ìì¬
	SLegion legion;

	int up;
	int right;
	int left;
	int down;

	float angle;
public:
	ShotFactory(const Player& player, const EnemyFactory& enemyfactory);
	~ShotFactory();

	// ’e‚ğì‚é
	// shotType...’e‚Ì–¼‘O
	Shot* Create(std::string shotType, Vector2f pos, int Speed, int movePtn, int level, int shooter);

	// ’e‚ÌW‡‘Ì‚ğ•Ô‚·
	SLegion& GetLegion();
	// ‘¼‚Ì‚à‚Ì‚É“–‚½‚Á‚½’e‚ğÁ‚·
	void ShotDelete();
	void OutofScreen(void);

	double SetAngle(std::string shotType, Vector2f pos, int shooter,int cnt,int);
	double SetTracking(std::string shotType, Vector2f pos,int shooter);
};

