#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class ShotRadiation : public Shot
{
	friend ShotFactory;
private:
	ShotRadiation(const Player& player, const EnemyFactory& enemyfactory/*, const Enemy& enemy*/);
	ShotRadiation(const ShotRadiation&);
	void operator=(const ShotRadiation&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (ShotRadiation::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;

	// 座標(x,y)を(xc,yc)を中心にthetaラジアン回転させた座標を(*xp,*yp)に返す関数
	void rotation2D(float * xp, float * yp, float x, float y, float xc, float yc, float theta);

	float range;
public:
	~ShotRadiation();

	void Update();
	void Draw();
	
};
