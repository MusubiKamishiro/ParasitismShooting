#pragma once
#include "../../Geometry.h"
#include <list>
#include <map>

class Shot;
class Player;
class EnemyFactory;

typedef std::list<Shot*> SLegion;	// 弾の集合体の型

class ShotFactory
{
private:
	const Player& player;
	const EnemyFactory& enemyfactory;
	
	std::map<std::string, Shot*> originalShot;	// 弾の元となるmapの作成
	SLegion legion;

	int up;
	int right;
	int left;
	int down;

	float angle;
public:
	ShotFactory(const Player& player, const EnemyFactory& enemyfactory);
	~ShotFactory();

	// 弾を作る
	// shotType...弾の名前
	Shot* Create(std::string shotType, Vector2f pos, int Speed, int movePtn, int level, int shooter);

	// 弾の集合体を返す
	SLegion& GetLegion();
	// 他のものに当たった弾を消す
	void ShotDelete();
	void OutofScreen(void);

	float SetAngle(std::string shotType, Vector2f pos, int shooter, int cnt, int);
};
