#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;


// —”‚É‚æ‚è•ûŒü‚ªŒˆ’è‚·‚é’e
class Random : public Shot
{
	friend ShotFactory;
private:
	Random(const Player& player, const EnemyFactory& enemyfactory);
	Random(const Random&);
	void operator=(const Random&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (Random::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~Random();

	void Update();
	void Draw();
	
};
