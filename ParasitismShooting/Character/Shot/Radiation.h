#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class Radiation : public Shot
{
	friend ShotFactory;
private:
	Radiation(const Player& player, const EnemyFactory& enemyfactory/*, const Enemy& enemy*/);
	Radiation(const Radiation&);
	void operator=(const Radiation&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (Radiation::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;

	void rotation2D(float * xp, float * yp, float x, float y, float xc, float yc, float theta);

	float range;
public:
	~Radiation();

	void Update();
	void Draw();
	
};
