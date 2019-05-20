#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class ShotShotgun : public Shot
{
	friend ShotFactory;
private:
	ShotShotgun(const Player& player, const EnemyFactory& enemyfactory);
	ShotShotgun(const ShotShotgun&);
	void operator=(const ShotShotgun&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (ShotShotgun::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~ShotShotgun();

	void Update();
	void Draw();
	
};
