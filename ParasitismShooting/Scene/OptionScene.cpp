#include "OptionScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "SceneManager.h"
#include "../Menu/OptionMenu.h"
#include "TitleScene.h"

void OptionScene::FadeinUpdate(const Peripheral & p)
{
	if (pal >= 255)
	{
		pal = 255;
		updater = &OptionScene::WaitUpdate;
	}
	else
	{
		pal += 20;
	}
}

void OptionScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal <= 0)
	{
		SceneManager::Instance().ChangeScene(std::make_unique <TitleScene>());
	}
	else
	{
		pal -= 20;
	}
}

void OptionScene::WaitUpdate(const Peripheral & p)
{
	if (omenu->Update(p))
	{
		pal = 255;
		updater = &OptionScene::FadeoutUpdate;
	}
}

OptionScene::OptionScene()
{
	pal = 0;
	updater = &OptionScene::FadeinUpdate;

	omenu.reset(new OptionMenu());
}


OptionScene::~OptionScene()
{
}

void OptionScene::Update(const Peripheral& p)
{
	(this->*updater)(p);
}

void OptionScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);

	omenu->Draw();

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);
}
