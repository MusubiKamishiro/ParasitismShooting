#include "PauseMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Menu.h"


PauseMenu::PauseMenu()
{
	menu.reset(new Menu());

	menu->menuTitle.push_back({ Vector2(menu->GetStringPosx("�ꎞ��~��"), (menu->ssize.y) / 3), "�ꎞ��~��", 0xff00ff });

	menu->menudata.push_back({ Vector2(menu->GetStringPosx("�Q�[���𑱂���"), (menu->ssize.y) / 3 + 100), "�Q�[���𑱂���", 0xff00ff });
	menu->menudata.push_back({ Vector2(menu->GetStringPosx("�^�C�g���ɖ߂�"), (menu->ssize.y) / 3 + 130), "�^�C�g���ɖ߂�", 0xff00ff });
}


PauseMenu::~PauseMenu()
{
}

bool PauseMenu::Update(const Peripheral& p, bool& flag)
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

void PauseMenu::Draw()
{
	menu->Draw(Vector2(5, 5));
}


