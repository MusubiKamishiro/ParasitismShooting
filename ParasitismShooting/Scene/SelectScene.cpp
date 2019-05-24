#include "SelectScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "GamePlayingScene.h"
#include "../SelectMenu.h"
#include "../Character/CharacterObject.h"
#include "../Score.h"


void SelectScene::FadeinUpdate(const Peripheral & p)
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

void SelectScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal <= 0)
	{
		Score::Instance().InitScore(true);
		Game::Instance().ChangeScene(new GamePlayingScene(1));
	}
	else
	{
		pal -= 20;
	}
}

SelectScene::SelectScene()
{
	img = DxLib::LoadGraph("img/bg.png");
	updater = &SelectScene::FadeinUpdate;

	smenu.reset(new SelectMenu());
}


SelectScene::~SelectScene()
{
}

void SelectScene::Update(const Peripheral& p)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	DxLib::DrawExtendGraph(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, img, true);
	DxLib::DrawString(50, 50, "SelectScene", 0x000000);
	
	if (smenu->Update(p))
	{
		pal = 255;
		updater = &SelectScene::FadeoutUpdate;
	}
	smenu->Draw();

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);

	(this->*updater)(p);
}