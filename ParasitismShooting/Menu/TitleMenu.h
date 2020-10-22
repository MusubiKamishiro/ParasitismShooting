#pragma once
#include <memory>
#include "../Geometry.h"

class Menu;
class Peripheral;

class TitleMenu
{
private:
	std::shared_ptr<Menu> menu;

public:
	TitleMenu();
	~TitleMenu();

	bool Update(const Peripheral& p, bool& flag);
	void Draw();
};
