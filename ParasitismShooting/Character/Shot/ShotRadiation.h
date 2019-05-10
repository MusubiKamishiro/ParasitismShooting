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
	
	void (ShotRadiation::*updater)();

	const Player& player;
	const Enemy& enemy;


public:
	~ShotRadiation();

	void Update();
	void Draw();
	
};
