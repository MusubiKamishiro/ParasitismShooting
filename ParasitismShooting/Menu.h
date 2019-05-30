#pragma once
#include <vector>
#include <memory>
#include "Geometry.h"

class GameScreen;
class Peripheral;

struct MenuData
{
	Vector2 pos;		// ���W
	const char* name;	// �\������镶��
	unsigned int color;	// �F
};

class Menu
{
public:
	std::shared_ptr<GameScreen> gs;
	std::vector<MenuData> menudata;
	std::vector <MenuData> menuTitle;
	int selcnt;
	Vector2 ssize;

	// �����̕��������ʂ̒����ɑ�������W��Ԃ�
	int GetStringCenterPosx(const std::string& name);
	// �����̕�������E�l�߂ɂ�����W��Ԃ�
	int GetStringRightPosx(const std::string& name, const int& rpos);

public:
	Menu();
	~Menu();

	void Update(const Peripheral &p);
	void Draw(const Vector2& shiftpos);

	bool decideFlag;
};

