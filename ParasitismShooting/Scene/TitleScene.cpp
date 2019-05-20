#include "TitleScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "SelectScene.h"
#include "../TitleMenu.h"
#include "OptionScene.h"

void TitleScene::FadeinUpdate(const Peripheral & p)
{
	if (pal == 255)
	{
		;
	}
	else
	{
		pal++;
	}
}

void TitleScene::FadeoutUpdate(const Peripheral & p)
{
	if (optionflag)
	{
		Game::Instance().ChangeScene(new OptionScene());
	}
	else if (pal <= 0)
	{
		Game::Instance().ChangeScene(new SelectScene());
	}
	else
	{
		//pal -= 5;
		pal -= 20;
	}
}

TitleScene::TitleScene()
{
	titleImage = DxLib::LoadGraph("img/title.png");
	optionflag = false;
	updater = &TitleScene::FadeinUpdate;

	tmenu.reset(new TitleMenu());
}


TitleScene::~TitleScene()
{
}

void TitleScene::Update(const Peripheral& p)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	DxLib::DrawExtendGraph(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, titleImage, true);

	if (tmenu->Update(p, optionflag))
	{
		pal = 255;
		updater = &TitleScene::FadeoutUpdate;
	}
	if (optionflag)
	{
		updater = &TitleScene::FadeoutUpdate;
	}
	
	tmenu->Draw();

	(this->*updater)(p);
}
