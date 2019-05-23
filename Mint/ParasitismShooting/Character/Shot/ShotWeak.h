#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class ShotWeak : public Shot
{
	friend ShotFactory;
private:
	ShotWeak(const Player& player, const EnemyFactory& enemyfactory);
	ShotWeak(const ShotWeak&);
	void operator=(const ShotWeak&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (ShotWeak::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~ShotWeak();

	void Update();
	void Draw();
	
};
