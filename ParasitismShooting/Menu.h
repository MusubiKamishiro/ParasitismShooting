#pragma once
#include <vector>
#include <memory>
#include "Geometry.h"

class GameScreen;
class Peripheral;

struct MenuData
{
	Vector2 pos;		// ç¿ïW
	const char* name;	// ï\é¶Ç≥ÇÍÇÈï∂éö
	unsigned int color;	// êF
};

class Menu
{
public:
	std::shared_ptr<GameScreen> gs;
	std::vector<MenuData> menudata;
	std::vector <MenuData> menuTitle;
	int selcnt;
	Vector2 ssize;

	int GetStringPosx(const std::string& name);

public:
	Menu();
	~Menu();

	void Update(const Peripheral &p);
	void Draw(const Vector2& shiftpos);

	bool decideFlag;
};

