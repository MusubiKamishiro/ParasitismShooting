#include "HUD.h"
#include "Game.h"
#include <DxLib.h>


HUD::HUD() : ssize(Game::Instance().GetScreenSize()), hudPos(Vector2(ssize.x - 300, 0))
{
	img = DxLib::LoadGraph("img/283logo.png");
}


HUD::~HUD()
{
}

void HUD::Draw(const int& life)
{
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0xffffff, true);
	DxLib::DrawString(510, 50, "ç≈çÇìæì_\nìæì_\n\n\n\n\n\n\n\nÇªÇÃëºÇ¢ÇÎÇ¢ÇÎ", 0x000000);
	DxLib::DrawString(510, 104, "HP", 0x0000ff);

	for (int a = 0; a < life; a++)
	{
		DxLib::DrawString(550 + a * 20, 104, "Åö", 0x0000ff);
	}

	DxLib::DrawExtendGraph(500, 200, 800, 500, img, true);
}

const Vector2 HUD::GetHUDPos()const
{
	return hudPos;
}
