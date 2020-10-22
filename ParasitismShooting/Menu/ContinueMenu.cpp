#include "ContinueMenu.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "Menu.h"
#include "../KeyConfig.h"


ContinueMenu::ContinueMenu()
{
	menu.reset(new Menu());

	menu->menuTitle.push_back({ Vector2(menu->GetStringCenterPosx("コンティニューする？"), menu->ssize.y / 3), "コンティニューする？", 0xff00ff });
	menu->menuTitle.push_back({ Vector2(menu->GetStringCenterPosx("コインを入れてね"), menu->ssize.y / 3 + 30), "コインを入れてね", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("はい"), menu->ssize.y / 3 + 100), "はい", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringCenterPosx("いいえ"), menu->ssize.y / 3 + 130), "いいえ", 0xff00ff });
}


ContinueMenu::~ContinueMenu()
{
}

bool ContinueMenu::Update(const Peripheral & p, bool & flag)
{
	menu->Update(p);
	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)) /*&& !menu->decideFlag*/)
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

void ContinueMenu::Draw()
{
	menu->Draw(Vector2(5, 5));
}
