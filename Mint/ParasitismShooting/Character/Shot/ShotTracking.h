#pragma once
#include "Shot.h"

class Enemy;
class ShotFactory;

class ShotTracking : public Shot
{
	friend ShotFactory;
private:
	ShotTracking(const Player& player/*, const Enemy& enemy*/);
	ShotTracking(const ShotTracking&);
	void operator=(const ShotTracking&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (ShotTracking::*updater)();

	const Player& player;
	const Enemy& enemy;

public:
	~ShotTracking();

	void Update();
	void Draw();
	
};
