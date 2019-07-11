#include "OptionMenu.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "Menu.h"
#include "KeyConfigMenu.h"
#include "../KeyConfig.h"


OptionMenu::OptionMenu()
{
	configflag = false;

	menu.reset(new Menu());

	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("Key Config"), menu->ssize.y / 3 + 100), "Key Config", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("Back Title"), menu->ssize.y / 3 + 130), "Back Title", 0xff00ff });

	kcmenu.reset(new KeyConfigMenu());
}


OptionMenu::~OptionMenu()
{
}

bool OptionMenu::Update(const Peripheral & p)
{
	if (configflag)
	{
		kcmenu->Update(p, configflag);
	}
	else
	{
		menu->Update(p);
		if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)) && !menu->decideFlag)
		{
			
			if (menu->selcnt == 0)
			{
				configflag = true;
			}
			else if (menu->selcnt == 1)
			{
				menu->decideFlag = true;
				return true;
			}
		}
	}

	return false;
}

void OptionMenu::Draw()
{
	if (configflag)
	{
		kcmenu->Draw();
	}
	else
	{
		menu->Draw(Vector2(5, 5));
	}
}
