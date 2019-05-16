#pragma once
#include "Shot.h"

class Enemy;
class ShotFactory;

class ShotWeak : public Shot
{
	friend ShotFactory;
private:
	ShotWeak(const Player& player/*, const Enemy& enemy*/);
	ShotWeak(const ShotWeak&);
	void operator=(const ShotWeak&);

	Shot* Clone();

	void Move();
	void Delete();

	void (ShotWeak::*updater)();

	const Player& player;
	const Enemy& enemy;


public:
	~ShotWeak();

	void Update();
	void Draw();

};
