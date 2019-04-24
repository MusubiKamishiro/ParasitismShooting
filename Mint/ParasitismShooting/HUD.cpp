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

void HUD::Draw()
{

	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0xffffff, true);
	DxLib::DrawString(510, 50, "最高得点\n得点\n\nHP\n\n\n\n\nその他いろいろ", 0x000000);
	DxLib::DrawExtendGraph(500, 200, 800, 500, img, true);
}

const Vector2 HUD::GetHUDPos()const
{
	return hudPos;
}
