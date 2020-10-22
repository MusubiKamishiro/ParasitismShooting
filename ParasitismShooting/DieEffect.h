#pragma once
#include "Effect.h"

class EffectFactory;

class DieEffect :public Effect
{
	friend EffectFactory;
private:
	DieEffect();
	DieEffect(const DieEffect&);
	void operator=(const DieEffect&);

	Effect * Clone();

	int effect;

public:
	~DieEffect();

	void Update(const int& t);
	void Draw();
};
