#pragma once
#include "Shot.h"

class Enemy;
class ShotFactory;

class ShotShotgun : public Shot
{
	friend ShotFactory;
private:
	ShotShotgun(const Player& player/*, const Enemy& enemy*/);
	ShotShotgun(const ShotShotgun&);
	void operator=(const ShotShotgun&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (ShotShotgun::*updater)();

	const Player& player;
	const Enemy& enemy;


public:
	~ShotShotgun();

	void Update();
	void Draw();
	
};
