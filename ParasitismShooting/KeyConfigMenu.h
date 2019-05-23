#pragma once
#include <memory>
#include "Geometry.h"

class Menu;
class Peripheral;

class KeyConfigMenu
{
private:
	std::shared_ptr<Menu> menu;

public:
	KeyConfigMenu();
	~KeyConfigMenu();

	bool Update(const Peripheral& p, bool& flag);
	void Draw();
};

