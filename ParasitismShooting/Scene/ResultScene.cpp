#include "ResultScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "TitleScene.h"
#include <string>

void ResultScene::FadeinUpdate(const Peripheral & p)
{
	if (p.IsTrigger(PAD_INPUT_8))
	{
		pal = 255;
		updater = &ResultScene::FadeoutUpdate;
	}
	
	if (pal == 255)
	{
		;
	}
	else
	{
		pal++;
	}
}

void ResultScene::FadeoutUpdate(const Peripheral & p)
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

ResultScene::ResultScene(const unsigned int& score)
{
	updater = &ResultScene::FadeinUpdate;
	totalScore = score;
}


ResultScene::~ResultScene()
{
}

void ResultScene::Update(const Peripheral& p)
{
	(this->*updater)(p);
	DxLib::DrawString(50, 50, "ResultScene", 0xffffff);
	DxLib::DrawString(100, 100, std::to_string(totalScore).c_str(), 0xffffff);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
}
