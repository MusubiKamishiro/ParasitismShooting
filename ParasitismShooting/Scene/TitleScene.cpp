#include "TitleScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "../TitleMenu.h"
#include "OptionScene.h"
#include "../Sound.h"


void TitleScene::FadeinUpdate(const Peripheral & p)
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

void TitleScene::FadeoutUpdate(const Peripheral & p)
{
	if (optionflag)
	{
		SceneManager::Instance().ChangeScene(std::make_unique<OptionScene>());
	}
	else if (pal <= 0)
	{
		SceneManager::Instance().ChangeScene(std::make_unique <SelectScene>());
	}
	else
	{
		pal -= 20;
	}
}

TitleScene::TitleScene()
{
	titleImage = DxLib::LoadGraph("img/title.png");
	optionflag = false;
	updater = &TitleScene::FadeinUpdate;

	tmenu.reset(new TitleMenu());
	Sound::Instance().AddBGM("joker.mp3");
}


TitleScene::~TitleScene()
{
}

void TitleScene::Update(const Peripheral& p)
{
	Sound::Instance().PlayBGM(false);

	if (tmenu->Update(p, optionflag))
	{
		pal = 255;
		updater = &TitleScene::FadeoutUpdate;
	}
	
	(this->*updater)(p);
}

void TitleScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	DxLib::DrawExtendGraph(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, titleImage, true);

	tmenu->Draw();

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);

}
