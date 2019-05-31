#include "OptionScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "../OptionMenu.h"
#include "TitleScene.h"

void OptionScene::FadeinUpdate(const Peripheral & p)
{
	if (pal >= 255)
	{
		pal = 255;
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
		Game::Instance().ChangeScene(new TitleScene());
	}
	else
	{
		pal -= 20;
	}
}

OptionScene::OptionScene()
{
	updater = &OptionScene::FadeinUpdate;

	omenu.reset(new OptionMenu());
}


OptionScene::~OptionScene()
{
}

void OptionScene::Update(const Peripheral& p)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);

	if (omenu->Update(p))
	{
		pal = 255;
		updater = &OptionScene::FadeoutUpdate;
	}
	
	omenu->Draw();

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);

	(this->*updater)(p);
}
