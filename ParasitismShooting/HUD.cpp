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

void HUD::Draw(const int& life, const bool& flag, const int& parascnt, const unsigned int& ccount)
{
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0xffffff, true);
	
	score.Update();
	score.Draw(Vector2(510, 50));

	// 寄生してるかどうかでHPの色を分ける
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
		DxLib::DrawString(550 + a * 24, 150, "★", lifeColor);
	}

	DxLib::DrawFormatString((ssize.x - 100) - DxLib::GetDrawStringWidth("ParasCount　000", std::strlen("ParasCount　000")), 250, 0x000000, "ParasCount　%03d", parascnt);
	DxLib::DrawFormatString((ssize.x - 100) - DxLib::GetDrawStringWidth("ContinueCount　000", std::strlen("ContinueCount　000")), 280, 0x000000, "ContinueCount　%03d", ccount);
}

const Vector2 HUD::GetHUDPos()const
{
	return hudPos;
}
