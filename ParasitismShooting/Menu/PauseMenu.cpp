#include "PauseMenu.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "Menu.h"
#include "../KeyConfig.h"


PauseMenu::PauseMenu()
{
	menu.reset(new Menu());

	menu->menuTitle.push_back({ Vector2(menu->GetStringCenterPosx("一時停止中"), (menu->ssize.y) / 3), "一時停止中", 0xff00ff });

	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("ゲームを続ける"), (menu->ssize.y) / 3 + 100), "ゲームを続ける", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("タイトルに戻る"), (menu->ssize.y) / 3 + 130), "タイトルに戻る", 0xff00ff });
}


PauseMenu::~PauseMenu()
{
}

bool PauseMenu::Update(const Peripheral& p, bool& flag)
{
	menu->Update(p);
	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)))
	{
		if (menu->selcnt == 0)
		{
			flag = false;
		}
		else if (menu->selcnt == 1)
		{
			return true;
		}
	}

	return false;
}

void PauseMenu::Draw()
{
	menu->Draw(Vector2(5, 5));
}
