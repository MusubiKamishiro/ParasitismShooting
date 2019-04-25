#pragma once
#include "Geometry.h"
#include <memory>

class GameScreen;

class BackGround
{
private:
	int BGimg;
	Vector2 gssize;

	std::shared_ptr<GameScreen> gs;

public:
	BackGround();
	~BackGround();

	void Draw(const int& time);
};

