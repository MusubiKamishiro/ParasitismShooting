#pragma once
#include "Geometry.h"
class HUD
{
private:
	const Vector2 ssize;
	const Vector2 hudPos;

public:
	HUD();
	~HUD();

	void Draw();

	const Vector2 GetHUDPos()const;
};

