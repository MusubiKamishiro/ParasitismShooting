#include "HalfResultScene.h"
#include <DxLib.h>
#include <string>
#include <random>
#include "../Peripheral.h"
#include "../Game.h"
#include "../GameScreen.h"
#include "GamePlayingScene.h"
#include "../KeyConfig.h"
#include "../Score.h"


HalfResultScene::HalfResultScene()
{
	sboxes.resize(0);
	boxCnt = 0;

	gs.reset(new GameScreen());
	gssize = gs->GetGSSize();

	flag = false;
	returnFlag = false;
	img = DxLib::LoadGraph("img/result.png");
	imgSize = Vector2(842, 1191);
	boxlength = Vector2(gssize.x - gs->outscreen, gssize.y - gs->outscreen);
	boxlength /= 5;
	imgSize /= 5;


	for (int y = gs->outscreen; y < gssize.y; y += boxlength.y)
	{
		for (int x = gs->outscreen; x < gssize.x; x += boxlength.x)
		{
			sboxes.push_back({ Box(x, y, x + boxlength.x, y + boxlength.y), false });
		}
	}
}


HalfResultScene::~HalfResultScene()
{
}

bool HalfResultScene::Update(const Peripheral& p)
{
	//Score::Instance().Update();

	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)) && returnFlag)
	{
		flag = true;
		if (boxCnt == sboxes.size())
		{
			boxCnt = 0;
		}
	}

	if (flag)
	{
		if (SubBox())
		{
			returnFlag = false;
		}
	}
	else
	{
		if (AddBox())
		{
			returnFlag = true;
		}
	}
	
	return returnFlag;
}

void HalfResultScene::Draw()
{
	for (auto& b : sboxes)
	{
		if (b.drawflag)
		{
			DxLib::DrawRectExtendGraph(b.box.dotA.x, b.box.dotA.y, b.box.dotB.x, b.box.dotB.y,
				(b.box.dotA.x - gs->outscreen) / boxlength.x * imgSize.x, (b.box.dotA.y - gs->outscreen) / boxlength.x * imgSize.y, 
				imgSize.x, imgSize.y, img, true);
		}
	}
	DxLib::DrawString(60, 60, "’†ŠÔƒŠƒUƒ‹ƒg", 0x00ff00);
	DxLib::DrawString(110, 160, std::to_string(Score::Instance().GetNowScore()).c_str(), 0x00ff00);
}

bool HalfResultScene::AddBox()
{
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	for (auto& b : sboxes)
	{
		if (!b.drawflag)
		{
			if ((engine() % (sboxes.size() - boxCnt)) == 0)
			{
				b.drawflag = true;
				++boxCnt;
				break;
			}
		}
	}

	if (boxCnt == sboxes.size())
	{
		return true;
	}
	return false;
}

bool HalfResultScene::SubBox()
{
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	for (auto& b : sboxes)
	{
		if (b.drawflag)
		{
			if ((engine() % (sboxes.size() - boxCnt)) == 0)
			{
				b.drawflag = false;
				++boxCnt;
				break;
			}
		}
	}

	if (boxCnt == sboxes.size())
	{
		return true;
	}
	return false;
}
