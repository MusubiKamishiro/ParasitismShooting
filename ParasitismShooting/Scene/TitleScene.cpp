#include "TitleScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "../Menu/TitleMenu.h"
#include "OptionScene.h"
#include "../Sound.h"


void TitleScene::FadeinUpdate(const Peripheral & p)
{
	if (pal >= 255)
	{
		pal = 255;
		updater = &TitleScene::WaitUpdate;
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

void TitleScene::WaitUpdate(const Peripheral & p)
{
	if (tmenu->Update(p, optionflag))
	{
		pal = 255;
		updater = &TitleScene::FadeoutUpdate;
	}
}

TitleScene::TitleScene()
{
	pal = 0;

	titleImage = DxLib::LoadGraph("img/title.png");
	titleNameImage = DxLib::LoadGraph("img/titlename.png");
	optionflag = false;
	updater = &TitleScene::FadeinUpdate;

	tmenu.reset(new TitleMenu());
	Sound::Instance().AddBGM("joker.mp3");
	ssize = Game::Instance().GetScreenSize();
	time = 0;
}


TitleScene::~TitleScene()
{
}

void TitleScene::Update(const Peripheral& p)
{
	Sound::Instance().PlayBGM(false);
	++time;

	(this->*updater)(p);
}

void TitleScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	DxLib::DrawExtendGraph(0, 0, ssize.x, ssize.y, titleImage, true);

	DxLib::DrawGraph(0, 0, titleNameImage, true);

	tmenu->Draw();

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);
}
