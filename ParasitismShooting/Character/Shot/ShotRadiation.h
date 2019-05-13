#pragma once
#include "Shot.h"

class Enemy;
class ShotFactory;

class ShotRadiation : public Shot
{
	friend ShotFactory;
private:
	ShotRadiation(const Player& player/*, const Enemy& enemy*/);
	ShotRadiation(const ShotRadiation&);
	void operator=(const ShotRadiation&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (ShotRadiation::*updater)();

	const Player& player;
	const Enemy& enemy;

	void rotation2D(float * xp, float * yp, float x, float y, float xc, float yc, float theta);

public:
	~ShotRadiation();

	void Update();
	void Draw();
	
};
