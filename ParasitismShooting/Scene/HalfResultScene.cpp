#include "HalfResultScene.h"
#include <DxLib.h>
#include <string>
#include "../Peripheral.h"
#include "../Game.h"
#include "GamePlayingScene.h"
#include "../KeyConfig.h"
#include "../Score.h"
#include "../HUD.h"

void HalfResultScene::FadeinUpdate(const Peripheral & p)
{
	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)))
	{
		pal = 255;
		updater = &HalfResultScene::FadeoutUpdate;
	}
	
	if (pal >= 255)
	{
		;
	}
	else
	{
		pal += 20;
	}
}

void HalfResultScene::FadeoutUpdate(const Peripheral & p)
{
	Game::Instance().ChangeScene(new GamePlayingScene(nextstage, nowstate));
}

HalfResultScene::HalfResultScene(const unsigned int& nowstagenum, const CharaData& cdata)
{
	updater = &HalfResultScene::FadeinUpdate;

	nextstage = nowstagenum + 1;
	nowstate = cdata;

	hud.reset(new HUD());
}


HalfResultScene::~HalfResultScene()
{
}

void HalfResultScene::Update(const Peripheral& p)
{
	Score::Instance().Update();

	hud->Draw(0, false);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);

	DxLib::DrawString(0, 0, "’†ŠÔƒŠƒUƒ‹ƒg", 0x00ff00);
	DxLib::DrawString(50, 100, std::to_string(Score::Instance().GetNowScore()).c_str(), 0x00ff00);

	(this->*updater)(p);
}
