#include "HUD.h"
#include "Game.h"
#include <DxLib.h>


HUD::HUD() : ssize(Game::Instance().GetScreenSize()), hudPos(Vector2(ssize.x - 300, 0))
{
	lifeColor = 0x0000ff;
}


HUD::~HUD()
{
}

void HUD::Draw(const int& life, const bool& flag)
{
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0xffffff, true);
	DxLib::DrawString(510, 50, "ç≈çÇìæì_\nìæì_\n\n\n\n\n\n\n\nÇªÇÃëºÇ¢ÇÎÇ¢ÇÎ", 0x000000);
	

	if (flag)
	{
		lifeColor = 0xff0000;
	}
	else
	{
		lifeColor = 0x0000ff;
	}

	DxLib::DrawString(515, 120, "HP", lifeColor);
	for (int a = 1; a < life; a++)
	{
		DxLib::DrawString(550 + a * 24, 120, "Åö", lifeColor);
	}
}

const Vector2 HUD::GetHUDPos()const
{
	return hudPos;
}
