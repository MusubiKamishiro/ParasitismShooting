#pragma once
#include <memory>
#include <string>
#include "Geometry.h"

enum PauseMenuList
{
	resume,
	end,
	max
};

class GameScreen;
class Peripheral;

class PauseMenu
{
private:
	std::shared_ptr<GameScreen> gs;
	Vector2 ssize;

	std::string pause, resume, end;

	int GetStringPosx(const std::string& name);

public:
	PauseMenu();
	~PauseMenu();

	void Update(const Peripheral& p);
	void Draw();
};

