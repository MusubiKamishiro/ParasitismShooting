#include "GameScreen.h"
#include <DxLib.h>
#include "Game.h"


GameScreen::GameScreen() : outscreen(60)
{
	Vector2 ssize = Game::Instance().GetScreenSize();

	gssize = Vector2((ssize.x - (300 + 20) + outscreen * 2), (ssize.y - 40 + outscreen * 2));

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
	DxLib::SetDrawScreen(DX_SCREEN_BACK);		// ï`âÊêÊÇñﬂÇ∑

	DxLib::DrawRectGraph(20, 20, outscreen, outscreen, gssize.x - outscreen * 2, gssize.y - outscreen * 2, screen, true, false);
}

const Vector2 GameScreen::GetGSSize() const
{
	return Vector2(gssize.x - outscreen, gssize.y - outscreen);
}
