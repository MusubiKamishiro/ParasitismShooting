#pragma once
#include "Shot.h"

class Enemy;
class ShotFactory;

class ShotRandom : public Shot
{
	friend ShotFactory;
private:
	ShotRandom(const Player& player/*, const Enemy& enemy*/);
	ShotRandom(const ShotRandom&);
	void operator=(const ShotRandom&);

	Shot* Clone();

	void Move();
	
	void (ShotRandom::*updater)();

	const Player& player;
	const Enemy& enemy;


public:
	~ShotRandom();

	void Update();
	void Draw();
	
};
