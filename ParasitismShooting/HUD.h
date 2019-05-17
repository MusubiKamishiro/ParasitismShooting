#pragma once
#include <memory>
#include "Geometry.h"


class HUD
{
private:
	const Vector2 ssize;
	const Vector2 hudPos;
	int lifeColor;
	unsigned int score;
	unsigned int upScore;
	unsigned int highScore;

public:
	HUD();
	~HUD();

	void Update();
	void Draw(const int& life, const bool& flag);
	void AddScore(const unsigned int& inscore);
	void DelScore();

	const Vector2 GetHUDPos()const;
};

