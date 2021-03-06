#include "DescriptionScene.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "../Peripheral.h"
#include "../Game.h"


void DescriptionScene::FadeinUpdate(const Peripheral & p)
{
	if (pal >= 255)
	{
		pal = 255;
		updater = &DescriptionScene::WaitUpdate;
	}
	else
	{
		pal += 20;
	}
}

void DescriptionScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal < 0)
	{
		SceneManager::Instance().PopScene();
	}
	else
	{
		pal -= 20;
	}
	
}

void DescriptionScene::WaitUpdate(const Peripheral & p)
{
	if (p.IsTrigger(key.GetNowKey(BOMB)))
	{
		updater = &DescriptionScene::FadeoutUpdate;
	}
}

DescriptionScene::DescriptionScene()
{
	pal = 0;

	img = DxLib::LoadGraph("img/description.png");
	updater = &DescriptionScene::FadeinUpdate;
}


DescriptionScene::~DescriptionScene()
{
}

void DescriptionScene::Update(const Peripheral & p)
{
	++time;
	(this->*updater)(p);
}

void DescriptionScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);

	DxLib::DrawExtendGraph(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y,  img, true);

	if (time / 60 % 2 == 0)
	{
		DxLib::DrawString(550, 400, "Cancelボタンで戻る", 0x000000);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);
}
