#include "KeyConfigMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Menu.h"
#include "KeyConfig.h"


KeyConfigMenu::KeyConfigMenu()
{
	menu.reset(new Menu());

	menu->menuTitle.push_back({ Vector2(0, 0), "Key Config", 0xffffff });

	menu->menudata.push_back({ Vector2(menu->GetStringPosx("Attack"), 100), "Attack", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("Cancel"), 150), "Cancel", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("Bomb"), 200), "Bomb", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("Slow"), 250), "Slow", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("Pause"), 300), "Pause", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("Exit"), 400), "Exit", 0xff00ff });
}


KeyConfigMenu::~KeyConfigMenu()
{
}

bool KeyConfigMenu::Update(const Peripheral & p, bool& flag)
{
	menu->Update(p);

	if ((menu->selcnt == menu->menudata.size() - 1) && !menu->decideFlag)
	{
		if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)) && !menu->decideFlag)
		{
			flag = false;
			menu->decideFlag = true;
		}
	}
	else
	{
		for (int i = 0; i < (ALL_KEY_MAX - 4); ++i)
		{
			if (p.IsTrigger(KeyConfig::Instance().GetAllKey(i)))
			{
				KeyConfig::Instance().SetChangeKey(menu->selcnt, i);
			}
		}
	}
	
	return false;
}

void KeyConfigMenu::Draw()
{
	DxLib::SetFontSize(48);
	menu->Draw(Vector2(5, 5));
	DxLib::SetFontSize(24);
}
