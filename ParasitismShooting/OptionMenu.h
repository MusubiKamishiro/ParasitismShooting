#pragma once
#include <memory>
#include "Geometry.h"

class Menu;
class KeyConfigMenu;
class Peripheral;

class OptionMenu
{
private:
	std::shared_ptr<Menu> menu;
	std::shared_ptr<KeyConfigMenu> kcmenu;

	bool configflag;

public:
	OptionMenu();
	~OptionMenu();

	bool Update(const Peripheral& p/*, bool& flag*/);
	void Draw();
};

