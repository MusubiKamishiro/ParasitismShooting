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
	unsigned int cCount;

public:
	HUD();
	~HUD();

	void Update();
	void Draw(const int& life, const bool& flag);
	void AddScore(const unsigned int& inscore);
	void InitScore();
	void AddContinueCount();

	const Vector2 GetHUDPos()const;
	unsigned int GetScore()const;
	unsigned int GetContinueCount()const;
};

