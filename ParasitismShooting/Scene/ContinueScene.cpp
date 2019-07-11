#include "ContinueScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "../ContinueMenu.h"
#include "../Score.h"
#include "../KeyConfig.h"


void ContinueScene::FadeinUpdate(const Peripheral & p)
{
	updater = &ContinueScene::WaitUpdate;
}

void ContinueScene::FadeoutUpdate(const Peripheral & p)
{
	if (flag)
	{
		SceneManager::Instance().ChangeScene(std::make_unique <ResultScene>(Score::Instance().GetNowScore(), /*totalCCount*/0));
	}
	else
	{
		SceneManager::Instance().PopScene();
	}
}

void ContinueScene::WaitUpdate(const Peripheral & p)
{
	cmenu->Update(p, flag);

	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)))
	{
		updater = &ContinueScene::FadeoutUpdate;
	}
}

ContinueScene::ContinueScene()
{
	cmenu.reset(new ContinueMenu());
	flag = true;
	updater = &ContinueScene::FadeinUpdate;
}


ContinueScene::~ContinueScene()
{
}

void ContinueScene::Update(const Peripheral& p)
{
	(this->*updater)(p);
}

void ContinueScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);

	cmenu->Draw();

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);

}
