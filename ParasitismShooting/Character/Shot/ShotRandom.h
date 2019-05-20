#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class ShotRandom : public Shot
{
	friend ShotFactory;
private:
	ShotRandom(const Player& player, const EnemyFactory& enemyfactory);
	ShotRandom(const ShotRandom&);
	void operator=(const ShotRandom&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (ShotRandom::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~ShotRandom();

	void Update();
	void Draw();
	
};
