#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class Tracking : public Shot
{
	friend ShotFactory;
private:
	Tracking(const Player& player, const EnemyFactory& enemyfactory);
	Tracking(const Tracking&);
	void operator=(const Tracking&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (Tracking::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~Tracking();

	void Update();
	void Draw();
	
};
