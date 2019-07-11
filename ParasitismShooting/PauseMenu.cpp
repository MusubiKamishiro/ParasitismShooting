#include "PauseMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Menu.h"
#include "KeyConfig.h"


PauseMenu::PauseMenu()
{
	menu.reset(new Menu());

	menu->menuTitle.push_back({ Vector2(menu->GetStringCenterPosx("ˆêŽž’âŽ~’†"), (menu->ssize.y) / 3), "ˆêŽž’âŽ~’†", 0xff00ff });

	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("ƒQ[ƒ€‚ð‘±‚¯‚é"), (menu->ssize.y) / 3 + 100), "ƒQ[ƒ€‚ð‘±‚¯‚é", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("ƒ^ƒCƒgƒ‹‚É–ß‚é"), (menu->ssize.y) / 3 + 130), "ƒ^ƒCƒgƒ‹‚É–ß‚é", 0xff00ff });
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


