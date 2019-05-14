#include "HUD.h"
#include "Game.h"
#include <DxLib.h>


HUD::HUD() : ssize(Game::Instance().GetScreenSize()), hudPos(Vector2(ssize.x - 300, 0))
{
}


HUD::~HUD()
{
}

void HUD::Draw(const int& life)
{
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0xffffff, true);
	DxLib::DrawString(510, 50, "ç≈çÇìæì_\nìæì_\n\n\n\n\n\n\n\nÇªÇÃëºÇ¢ÇÎÇ¢ÇÎ", 0x000000);
	DxLib::DrawString(515, 120, "HP", 0x0000ff);

	for (int a = 0; a < life; a++)
	{
		DxLib::DrawString(550 + a * 24, 120, "Åö", 0x0000ff);
	}
}

const Vector2 HUD::GetHUDPos()const
{
	return hudPos;
}
