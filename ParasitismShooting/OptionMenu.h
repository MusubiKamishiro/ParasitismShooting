#pragma once
#include <memory>
#include "Geometry.h"

class Menu;
class Peripheral;

class OptionMenu
{
private:
	std::shared_ptr<Menu> menu;

public:
	OptionMenu();
	~OptionMenu();

	bool Update(const Peripheral& p/*, bool& flag*/);
	void Draw();
};

