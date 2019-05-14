#pragma once
#include <memory>
#include <string>
#include "Geometry.h"

class GameScreen;
class Peripheral;

class PauseMenu
{
private:
	Vector2 ssize;

	std::string pause;

	std::shared_ptr<GameScreen> gs;

public:
	PauseMenu();
	~PauseMenu();

	void Update(const Peripheral& p);
	void Draw();
};

