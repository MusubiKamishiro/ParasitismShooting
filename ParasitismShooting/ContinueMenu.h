#pragma once
#include <memory>
#include <string>
#include "Geometry.h"

class Menu;
class Peripheral;

class ContinueMenu
{
private:
	std::shared_ptr<Menu> menu;

public:
	ContinueMenu();
	~ContinueMenu();

	bool Update(const Peripheral& p, bool& flag);
	void Draw();
};

