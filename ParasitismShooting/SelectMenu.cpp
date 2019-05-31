#include "SelectMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Menu.h"
#include "KeyConfig.h"


SelectMenu::SelectMenu()
{
	menu.reset(new Menu());

	menu->menudata.push_back({ Vector2(100, 100), "easy", 0x0000ff });
	menu->menudata.push_back({ Vector2(150, 150), "normal", 0x0000ff });
	menu->menudata.push_back({ Vector2(200, 200), "hard", 0x0000ff });
	menu->menudata.push_back({ Vector2(250, 250), "foolish", 0x0000ff });
}


SelectMenu::~SelectMenu()
{
}

bool SelectMenu::Update(const Peripheral & p, int& difficult)
{
	menu->Update(p);
	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)) && !menu->decideFlag)
	{
		difficult = menu->selcnt;
		menu->decideFlag = true;
		return true;
	}

	return false;
}

void SelectMenu::Draw()
{
	DxLib::SetFontSize(48);
	menu->Draw(Vector2(5, 5));
	DxLib::SetFontSize(24);
}
