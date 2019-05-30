#include "HalfResultScene.h"
#include <DxLib.h>
#include <string>
#include <random>
#include "../Peripheral.h"
#include "../GameScreen.h"
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
	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(ATTACK)) && returnFlag)
	{
		flag = true;
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

void HalfResultScene::Draw(const bool& flag)
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

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 / sboxes.size()) * boxCnt);
	
	std::string s;
	if (!flag)
	{
		s = "StageClearI";
	}
	else
	{
		s = "AllStageClearI";
	}
	
	DxLib::DrawString(((gssize.x + gs->outscreen) / 2 - DxLib::GetDrawStringWidth(s.c_str(), std::strlen(s.c_str())) / 2), 100, s.c_str(), 0x00ff00);

	DxLib::DrawString(GetStringRightPosx("Stage",			250), 200, "Stage", 0x00ff00);
	DxLib::DrawString(GetStringRightPosx("ParasCount",		250), 250, "ParasCount", 0x00ff00);
	DxLib::DrawString(GetStringRightPosx("BossHP",			250), 300, "BossHP", 0x00ff00);
	DxLib::DrawString(GetStringRightPosx("ContinueCount",	250), 350, "ContinueCount", 0x00ff00);
	DxLib::DrawString(GetStringRightPosx("Difficult",		250), 400, "Difficult", 0x00ff00);
	DxLib::DrawString(GetStringRightPosx("TotalBonus",		250), 450, "TotalBonus", 0x00ff00);

	for (int i = 0; i < 4; ++i)
	{
		DxLib::DrawString(270, 200 + i * 50, "*", 0x00ff00);
		DxLib::DrawString(370, 200 + i * 50, "=", 0x00ff00);
	}

	DxLib::DrawString(370, 400, "*", 0x00ff00);

	DxLib::DrawString(GetStringRightPosx("1000",	350), 200, "1000", 0x00ff00);
	DxLib::DrawString(GetStringRightPosx("10",		350), 250, "10", 0x00ff00);
	DxLib::DrawString(GetStringRightPosx("100",		350), 300, "100", 0x00ff00);
	DxLib::DrawString(GetStringRightPosx("-1000",	350), 350, "-1000", 0x00ff00);

	DxLib::DrawFormatString(400, 200, 0x00ff00, "%-8d", Score::Instance().stageBonus);
	DxLib::DrawFormatString(400, 250, 0x00ff00, "%-8d", Score::Instance().parasBonus);
	DxLib::DrawFormatString(400, 300, 0x00ff00, "%-8d", Score::Instance().bossHpBonus);
	DxLib::DrawFormatString(400, 350, 0x00ff00, "%-8d", Score::Instance().contBonus);
	DxLib::DrawFormatString(400, 400, 0x00ff00, "%-.1f", Score::Instance().diffBonus);
	DxLib::DrawFormatString(400, 450, 0x00ff00, "%-8d", Score::Instance().bonusScore);


	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
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
			if ((engine() % boxCnt) == 0)
			{
				b.drawflag = false;
				--boxCnt;
				break;
			}
		}
	}

	if (boxCnt == 0)
	{
		return true;
	}
	return false;
}

int HalfResultScene::GetStringRightPosx(const std::string & name, const int & rpos)
{
	return (rpos - DxLib::GetDrawStringWidth(name.c_str(), std::strlen(name.c_str())));
}
