#include "GameScreen.h"
#include <DxLib.h>
#include "Game.h"


GameScreen::GameScreen()
{
	Vector2 ssize = Game::Instance().GetScreenSize();
	screen = DxLib::MakeScreen((ssize.x - (300+20)), (ssize.y - 40));
	gssize = Vector2((ssize.x - (300 + 20)), (ssize.y - 40));
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
	DxLib::SetDrawScreen(DX_SCREEN_BACK);		// ï`âÊêÊÇñﬂÇ∑

	DxLib::DrawGraph(20, 20, screen, true);
}

const Vector2 GameScreen::GetGSSize() const
{
	return gssize;
}
