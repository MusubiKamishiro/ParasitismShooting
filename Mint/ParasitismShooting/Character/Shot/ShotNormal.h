#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class ShotNormal : public Shot
{
	friend ShotFactory;
private:
	ShotNormal(const Player& player, const EnemyFactory& enemyfactory);
	ShotNormal(const ShotNormal&);	
	void operator=(const ShotNormal&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (ShotNormal::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;


public:
	~ShotNormal();

	void Update();
	void Draw();
	
};
