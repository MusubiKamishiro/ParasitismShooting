#pragma once
#include <vector>
#include <memory>
#include "Geometry.h"

class GameScreen;
class Peripheral;

struct MenuData
{
	Vector2 pos;		// À•W
	const char* name;	// •\¦‚³‚ê‚é•¶š
	unsigned int color;	// F
};

class Menu
{
public:
	std::shared_ptr<GameScreen> gs;
	std::vector<MenuData> menudata;
	MenuData menuTitle;
	int selcnt;
	Vector2 ssize;

	int GetStringPosx(const std::string& name);

public:
	Menu();
	~Menu();

	void Update(const Peripheral &p);
	void Draw(const Vector2& shiftpos, const unsigned int& color);
};

