#include "TitleMenu.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "Menu.h"
#include "../KeyConfig.h"
#include "../Game.h"
#include "../Sound.h"

#include "../Scene/SceneManager.h"
#include "../Scene/DescriptionScene.h"


TitleMenu::TitleMenu()
{
	menu.reset(new Menu());

	menu->menudata.push_back({ Vector2(550, menu->ssize.y / 3 + 110), "Start", 0xff00ff });
	menu->menudata.push_back({ Vector2(550, menu->ssize.y / 3 + 140), "Option", 0xff00ff });
	//menu->menudata.push_back({ Vector2(550, menu->ssize.y / 3 + 170), "Help", 0xff00ff });
	menu->menudata.push_back({ Vector2(550, menu->ssize.y / 3 + 170), "Exit", 0xff00ff });
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
		/*else if (menu->selcnt == 2)
		{
			SceneManager::Instance().PushScene(std::make_unique<DescriptionScene>());
		}
		else if (menu->selcnt == 3)
		{
			Game::Instance().Terminate();
		}*/
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
