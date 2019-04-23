#pragma once
#include "Geometry.h"

class BackGround
{
private:
	int BGimg;
	Vector2 gssize;

public:
	BackGround();
	~BackGround();

	void Draw(const int& time);
};

