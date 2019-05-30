#pragma once
#include <memory>
#include "Geometry.h"
#include "Score.h"


class HUD
{
private:
	const Vector2 ssize;
	const Vector2 hudPos;
	int lifeColor;

	Score& score = Score::Instance();

public:
	HUD();
	~HUD();

	void Update();
	void Draw(const int& life, const bool& flag, const int& parascnt, const unsigned int& ccount);
	
	const Vector2 GetHUDPos()const;
};

