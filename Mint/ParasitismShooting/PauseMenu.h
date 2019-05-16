#pragma once
#include <memory>
#include <string>
#include "Geometry.h"


class Menu;
class Peripheral;

class PauseMenu
{
private:
	std::shared_ptr<Menu> menu;

public:
	PauseMenu();
	~PauseMenu();

	bool Update(const Peripheral& p, bool& flag);
	void Draw();
};

