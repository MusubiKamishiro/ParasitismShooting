#pragma once
#include <memory>
#include "Geometry.h"

class Menu;
class Peripheral;


class SelectMenu
{
private:
	std::shared_ptr<Menu> menu;

public:
	SelectMenu();
	~SelectMenu();

	bool Update(const Peripheral& p);
	void Draw();
};

