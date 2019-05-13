#pragma once
#include "Geometry.h"
#include <memory>


class HUD
{
private:
	const Vector2 ssize;
	const Vector2 hudPos;
	

public:
	HUD();
	~HUD();

	void Draw(const int& life);

	const Vector2 GetHUDPos()const;
};

