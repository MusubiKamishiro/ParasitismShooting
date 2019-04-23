#include "HalfResultScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "GamePlayingScene.h"

void HalfResultScene::FadeinUpdate(const Peripheral & p)
{
	if (p.IsTrigger(PAD_INPUT_8))
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
		Game::Instance().ChangeScene(new GamePlayingScene());
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
