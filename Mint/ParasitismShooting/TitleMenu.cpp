#include "TitleMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Menu.h"
#include "KeyConfig.h"
#include "Game.h"
#include "Sound.h"


TitleMenu::TitleMenu()
{
	menu.reset(new Menu());

	menu->menudata.push_back({ Vector2(550, menu->ssize.y / 3 + 100), "Start", 0xff00ff });
	menu->menudata.push_back({ Vector2(550, menu->ssize.y / 3 + 130), "Option", 0xff00ff });
	menu->menudata.push_back({ Vector2(550, menu->ssize.y / 3 + 160), "Exit", 0xff00ff });
}


TitleMenu::~TitleMenu()
{
}

bool TitleMenu::Update(const Peripheral & p, bool & flag)
{
	menu->Update(p);
	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)) && !menu->decideFlag)
	{
		menu->decideFlag = true;
		if (menu->selcnt == 0)
		{
			return true;
		}
		else if (menu->selcnt == 1)
		{
			flag = true;
			return true;
		}
		else if (menu->selcnt == 2)
		{
			Game::Instance().Terminate();
		}
	}

	return false;
}

void TitleMenu::Draw()
{
	menu->Draw(Vector2(5, 5));
}
