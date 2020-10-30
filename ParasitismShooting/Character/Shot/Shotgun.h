#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

// •ªU’e
// ƒŒƒxƒ‹‚É‚æ‚è•ªU”‚ª‘‚¦‚é
class Shotgun : public Shot
{
	friend ShotFactory;
private:
	Shotgun(const Player& player, const EnemyFactory& enemyfactory);
	Shotgun(const Shotgun&);
	void operator=(const Shotgun&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (Shotgun::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~Shotgun();

	void Update();
	void Draw();
	
};
