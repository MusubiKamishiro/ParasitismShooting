#include "SelectMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Menu.h"
#include "KeyConfig.h"


SelectMenu::SelectMenu()
{
	menu.reset(new Menu());

	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("easy"), menu->ssize.y / 3 + 100), "easy", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("normal"), menu->ssize.y / 3 + 130), "normal", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("hard"), menu->ssize.y / 3 + 160), "hard", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("foolish"), menu->ssize.y / 3 + 190), "foolish", 0xff00ff });
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
	menu->Draw(Vector2(5, 5));
}
