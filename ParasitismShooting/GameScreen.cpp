#include "GameScreen.h"
#include <DxLib.h>
#include "Game.h"


GameScreen::GameScreen()
{
	Vector2 ssize = Game::Instance().GetScreenSize();
	gssize = Vector2((ssize.x - (300 + 20)), (ssize.y - 40));

	screen = DxLib::MakeScreen(gssize.x, gssize.y);
}


GameScreen::~GameScreen()
{
}

void GameScreen::SetAndClearScreen()
{
	DxLib::SetDrawScreen(screen);
	DxLib::ClearDrawScreen();
}

void GameScreen::DrawAndChangeScreen()
{
	DxLib::SetDrawScreen(DX_SCREEN_BACK);		// �`����߂�

	DxLib::DrawGraph(20, 20, screen, true);
}

const Vector2 GameScreen::GetGSSize() const
{
	return gssize;
}
