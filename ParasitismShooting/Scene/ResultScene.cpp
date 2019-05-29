#include "ResultScene.h"
#include <DxLib.h>
#include <string>
#include "../Peripheral.h"
#include "../Game.h"
#include "TitleScene.h"
#include "../KeyConfig.h"

void ResultScene::FadeinUpdate(const Peripheral & p)
{
	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)))
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
		pal +=20;
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

ResultScene::ResultScene(const unsigned int& score, const unsigned int& cnum)
{
	updater = &ResultScene::FadeinUpdate;
	totalScore = score;
	continueNum = cnum;
}


ResultScene::~ResultScene()
{
}

void ResultScene::Update(const Peripheral& p)
{
	DxLib::DrawString(50, 50, "ResultScene", 0xffffff);
	DxLib::DrawString(100, 100, std::to_string(totalScore).c_str(), 0xffffff);
	DxLib::DrawString(100, 150, std::to_string(continueNum).c_str(), 0xffffff);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);
	(this->*updater)(p);
}
