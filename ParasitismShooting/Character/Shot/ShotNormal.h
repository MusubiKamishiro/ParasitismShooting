#pragma once
#include "Shot.h"

class ShotFactory;

class ShotNormal : public Shot
{
	friend ShotFactory;
private:
	ShotNormal(const Shot& shot);
	ShotNormal(const ShotNormal&);	
	void operator=(const ShotNormal&);

	Shot* Clone();

	void Move();
	
	void (ShotNormal::*updater)();

	const Shot& shot;


public:
	~ShotNormal();

	void Update();
	void Draw();
	
};
