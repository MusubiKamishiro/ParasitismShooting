#pragma once
#include <vector>
#include <memory>
#include "Geometry.h"

class GameScreen;
class Peripheral;

struct MenuData
{
	Vector2 pos;		// 座標
	const char* name;	// 表示される文字
	unsigned int color;	// 色
};

class Menu
{
public:
	std::shared_ptr<GameScreen> gs;
	std::vector<MenuData> menudata;
	std::vector <MenuData> menuTitle;
	int selcnt;
	Vector2 ssize;

	// 引数の文字列を画面の中央に揃える座標を返す
	int GetStringCenterPosx(const std::string& name);
	// 引数の文字列を右詰めにする座標を返す
	int GetStringRightPosx(const std::string& name, const int& rpos);

public:
	Menu();
	~Menu();

	void Update(const Peripheral &p);
	void Draw(const Vector2& shiftpos);

	bool decideFlag;
};

