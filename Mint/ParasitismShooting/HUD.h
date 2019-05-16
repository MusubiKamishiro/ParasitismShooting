#pragma once
#include <memory>
#include "Geometry.h"


class HUD
{
private:
	const Vector2 ssize;
	const Vector2 hudPos;
	int lifeColor;

public:
	HUD();
	~HUD();

	void Draw(const int& life, const bool& flag);

	const Vector2 GetHUDPos()const;
};

