#include "ContinueMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Menu.h"


ContinueMenu::ContinueMenu()
{
	menu.reset(new Menu());

	menu->menuTitle.push_back({ Vector2(menu->GetStringPosx("コンティニューする？"), menu->ssize.y / 3), "コンティニューする？", 0xff00ff });
	menu->menuTitle.push_back({ Vector2(menu->GetStringPosx("コインを入れてね"), menu->ssize.y / 3 + 30), "コインを入れてね", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("はい"), menu->ssize.y / 3 + 100), "はい", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("いいえ"), menu->ssize.y / 3 + 130), "いいえ", 0xff00ff });
}


ContinueMenu::~ContinueMenu()
{
}

bool ContinueMenu::Update(const Peripheral & p, bool & flag)
{
	menu->Update(p);
	if (p.IsTrigger(PAD_INPUT_2))
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
