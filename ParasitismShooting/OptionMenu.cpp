#include "OptionMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Menu.h"



OptionMenu::OptionMenu()
{
	menu.reset(new Menu());

	menu->menudata.push_back({ Vector2(menu->GetStringPosx("Key Config"), menu->ssize.y / 3 + 100), "Key Config", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("Back Title"), menu->ssize.y / 3 + 130), "Back Title", 0xff00ff });
}


OptionMenu::~OptionMenu()
{
}

bool OptionMenu::Update(const Peripheral & p)
{
	menu->Update(p);
	if (p.IsTrigger(PAD_INPUT_2))
	{
		if (menu->selcnt == 0)
		{
			//return true;
		}
		else if (menu->selcnt == 1)
		{
			return true;
		}
	}
	
	return false;
}

void OptionMenu::Draw()
{
	menu->Draw(Vector2(5, 5));
}
