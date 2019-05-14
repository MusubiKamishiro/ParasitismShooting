#include "GameScreen.h"
#include <DxLib.h>
#include <random>
#include "Game.h"


GameScreen::GameScreen() : outscreen(60)
{
	Vector2 ssize = Game::Instance().GetScreenSize();

	gssize = Vector2((ssize.x - (300 + 20) + outscreen * 2), (ssize.y - 40 + outscreen * 2));

	screen = DxLib::MakeScreen(gssize.x, gssize.y);

	swing = Vector2f(0, 0);
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
	DxLib::SetDrawScreen(DX_SCREEN_BACK);		// •`‰ææ‚ð–ß‚·

	if (DxLib::CheckHitKey(KEY_INPUT_H))
	{
		swing = Vector2f(outscreen / 3, outscreen / 3);
	}

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	if ((engine() % 4) == 0)
	{
		swing = Vector2f(swing.x, swing.y);
	}
	else if ((engine() % 4) == 1)
	{
		swing = Vector2f(-swing.x, swing.y);
	}
	else if ((engine() % 4) == 2)
	{
		swing = Vector2f(swing.x, -swing.y);
	}
	else if ((engine() % 4) == 3)
	{
		swing = Vector2f(-swing.x, -swing.y);
	}

	DxLib::DrawRectGraph(20, 20, outscreen + swing.x, outscreen + swing.y, gssize.x - outscreen * 2, gssize.y - outscreen * 2 , screen, true, false);

	if (std::abs(swing.x) > 0.5f)
	{
		swing *= 0.95f;
	}
	else
	{
		swing = Vector2f();
	}
}

void GameScreen::SetGaussFilter()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 32);
	DxLib::DrawBox(0, 0, gssize.x, gssize.y, 0x000000, true);
	DxLib::GraphFilter(screen, DX_GRAPH_FILTER_GAUSS, 16, 100);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

const Vector2 GameScreen::GetGSSize() const
{
	return Vector2(gssize.x - outscreen, gssize.y - outscreen);
}
