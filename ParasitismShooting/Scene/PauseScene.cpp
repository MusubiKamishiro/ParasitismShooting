#include "PauseScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "../PauseMenu.h"
#include "../KeyConfig.h"


void PauseScene::FadeinUpdate(const Peripheral & p)
{
	pal = 255;
	updater = &PauseScene::WaitUpdate;
}

void PauseScene::FadeoutUpdate(const Peripheral & p)
{
	if (flag)
	{
		SceneManager::Instance().ChangeScene(std::make_unique<TitleScene>());
	}
	else
	{
		SceneManager::Instance().PopScene();
	}
}

void PauseScene::WaitUpdate(const Peripheral & p)
{
	pmenu->Update(p, flag);

	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)))
	{
		updater = &PauseScene::FadeoutUpdate;
	}
}

PauseScene::PauseScene()
{
	flag = true;
	pmenu.reset(new PauseMenu());
	updater = &PauseScene::FadeinUpdate;
}


PauseScene::~PauseScene()
{
}

void PauseScene::Update(const Peripheral& p)
{
	(this->*updater)(p);
}

void PauseScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	
	pmenu->Draw();

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);

}
