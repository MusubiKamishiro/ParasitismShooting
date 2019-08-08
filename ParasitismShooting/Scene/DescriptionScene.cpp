#include "DescriptionScene.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "../Peripheral.h"


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
	if (p.IsTrigger(key.GetNowKey(CANCEL)))
	{
		updater = &DescriptionScene::FadeoutUpdate;
	}
}

DescriptionScene::DescriptionScene()
{
	img = DxLib::LoadGraph("img/description.png");
	updater = &DescriptionScene::FadeinUpdate;
}


DescriptionScene::~DescriptionScene()
{
}

void DescriptionScene::Update(const Peripheral & p)
{
	(this->*updater)(p);
}

void DescriptionScene::Draw()
{
	DxLib::DrawGraph(0, 0, img, true);
}
