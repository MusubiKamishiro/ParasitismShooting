#include "PauseScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "SceneManager.h"
#include "../PauseMenu.h"


void PauseScene::FadeinUpdate(const Peripheral & p)
{
	pal = 255;
	updater = &PauseScene::WaitUpdate;
}

void PauseScene::FadeoutUpdate(const Peripheral & p)
{
	SceneManager::Instance().PopScene();
}

void PauseScene::WaitUpdate(const Peripheral & p)
{
	bool pauseFlag = false;
	if (pmenu->Update(p, pauseFlag))
	{
		updater = &PauseScene::FadeoutUpdate;
	}
}

PauseScene::PauseScene()
{
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
	
	//gs->SetGaussFilter();
	pmenu->Draw();

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);

}
