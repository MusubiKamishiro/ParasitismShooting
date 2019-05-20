#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class ShotTracking : public Shot
{
	friend ShotFactory;
private:
	ShotTracking(const Player& player, const EnemyFactory& enemyfactory);
	ShotTracking(const ShotTracking&);
	void operator=(const ShotTracking&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (ShotTracking::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~ShotTracking();

	void Update();
	void Draw();
	
};
