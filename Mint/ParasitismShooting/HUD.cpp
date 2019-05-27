#include "HUD.h"
#include "Game.h"
#include <DxLib.h>
#include <string>


HUD::HUD() : ssize(Game::Instance().GetScreenSize()), hudPos(Vector2(ssize.x - 300, 0))
{
	lifeColor = 0x0000ff;
}


HUD::~HUD()
{
}

void HUD::Update()
{
	
}

void HUD::Draw(const int& life, const bool& flag)
{
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0xffffff, true);
	
	score.Update();
	score.Draw(Vector2(510, 50));

	// äÒê∂ÇµÇƒÇÈÇ©Ç«Ç§Ç©Ç≈HPÇÃêFÇï™ÇØÇÈ
	if (flag)
	{
		lifeColor = 0xff0000;
	}
	else
	{
		lifeColor = 0x0000ff;
	}

	DxLib::DrawString(515, 150, "HP", lifeColor);
	for (int a = 1; a < life; a++)
	{
		DxLib::DrawString(550 + a * 24, 150, "Åö", lifeColor);
	}
}

const Vector2 HUD::GetHUDPos()const
{
	return hudPos;
}
