#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class Normal : public Shot
{
	friend ShotFactory;
private:
	Normal(const Player& player, const EnemyFactory& enemyfactory);
	Normal(const Normal&);
	void operator=(const Normal&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (Normal::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~Normal();

	void Update();
	void Draw();
	
};
