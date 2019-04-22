#include "HUD.h"
#include "Game.h"
#include <DxLib.h>

HUD::HUD() : ssize(Game::Instance().GetScreenSize()), hudPos(Vector2(ssize.x - 300, 0))
{

}


HUD::~HUD()
{
}

void HUD::Draw()
{
	DxLib::DrawBox(hudPos.x, hudPos.y, ssize.x, ssize.y, 0x000000, true);
}

const Vector2 HUD::GetHUDPos()const
{
	return hudPos;
}
