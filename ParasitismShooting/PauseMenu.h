#pragma once
#include <memory>
#include "Geometry.h"

class GameScreen;
class Peripheral;

class PauseMenu
{
private:
	int img;
	Vector2 ssize;

	std::shared_ptr<GameScreen> gs;

public:
	PauseMenu();
	~PauseMenu();

	void Update(const Peripheral& p);
	void Draw();
};

