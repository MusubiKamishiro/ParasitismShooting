#include "ContinueMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Menu.h"


ContinueMenu::ContinueMenu()
{
	menu.reset(new Menu());

	menu->menuTitle.push_back({ Vector2(menu->GetStringPosx("�R���e�B�j���[����H"), menu->ssize.y / 3), "�R���e�B�j���[����H", 0xff00ff });
	menu->menuTitle.push_back({ Vector2(menu->GetStringPosx("�R�C�������Ă�"), menu->ssize.y / 3 + 30), "�R�C�������Ă�", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("�͂�"), menu->ssize.y / 3 + 100), "�͂�", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("������"), menu->ssize.y / 3 + 130), "������", 0xff00ff });
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
