#pragma once
#include <string>
#include "Geometry.h"

class EffectFactory;

class Effect
{
	friend EffectFactory;
protected:
	virtual Effect* Clone() = 0;

	Effect();

	Vector2f pos;
	int startTime;
	int drawTime;
	int time;

public:
	virtual ~Effect();

	virtual void Update(const int& time) = 0;
	virtual void Draw() = 0;
};

