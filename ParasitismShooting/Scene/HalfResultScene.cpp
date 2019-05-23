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
		Game::Instance().ChangeScene(new GamePlayingScene(1));
	}
	else
	{
		pal -= 20;
	}
}

HalfResultScene::HalfResultScene()
{
	updater = &HalfResultScene::FadeinUpdate;
}


HalfResultScene::~HalfResultScene()
{
}

void HalfResultScene::Update(const Peripheral& p)
{
	(this->*updater)(p);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
}
