#include "TitleScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "SelectScene.h"
#include "../TitleMenu.h"

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
	if (pal <= 0)
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

	if (tmenu->Update(p))
	{
		pal = 255;
		updater = &TitleScene::FadeoutUpdate;
	}
	
	tmenu->Draw();

	(this->*updater)(p);
}
