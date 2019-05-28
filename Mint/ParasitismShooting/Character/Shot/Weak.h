#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class Weak : public Shot
{
	friend ShotFactory;
private:
	Weak(const Player& player, const EnemyFactory& enemyfactory);
	Weak(const Weak&);
	void operator=(const Weak&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (Weak::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~Weak();

	void Update();
	void Draw();
	
};
