#include "HalfResultScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "GamePlayingScene.h"
#include "../KeyConfig.h"

void HalfResultScene::FadeinUpdate(const Peripheral & p)
{
	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)))
	{
		pal = 255;
		updater = &HalfResultScene::FadeoutUpdate;
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

void HalfResultScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal <= 0)
	{
		Game::Instance().ChangeScene(new GamePlayingScene(nextstage));
	}
	else
	{
		pal -= 20;
	}
}

HalfResultScene::HalfResultScene(const unsigned int& nowstagenum)
{
	updater = &HalfResultScene::FadeinUpdate;

	nextstage = nowstagenum + 1;
}


HalfResultScene::~HalfResultScene()
{
}

void HalfResultScene::Update(const Peripheral& p)
{
	DxLib::DrawString(0, 0, "中間リザルト", 0x00ff00);
	//DxLib::DrawString(0, 100, "次のステージは" + nextstage, 0x0000ff);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);

	(this->*updater)(p);
}
