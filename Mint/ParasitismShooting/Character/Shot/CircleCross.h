#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class CircleCross : public Shot
{
	friend ShotFactory;
private:
	CircleCross(const Player& player, const EnemyFactory& enemyfactory);
	CircleCross(const CircleCross&);
	void operator=(const CircleCross&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (CircleCross::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~CircleCross();

	void Update();
	void Draw();
	
};
