#pragma once
#include "Shot.h"

class Enemy;
class ShotFactory;

class ShotNormal : public Shot
{
	friend ShotFactory;
private:
	ShotNormal(const Player& player/*, const Enemy& enemy*/);
	ShotNormal(const ShotNormal&);	
	void operator=(const ShotNormal&);

	Shot* Clone();

	void Move();
	
	void (ShotNormal::*updater)();

	const Player& player;
	const Enemy& enemy;


public:
	~ShotNormal();

	void Update();
	void Draw();
	
};
