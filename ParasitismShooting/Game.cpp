#include "Game.h"
#include <DxLib.h>
#include "Peripheral.h"

#include "Scene/TitleScene.h"
#include "resource.h"


Game::Game() : ScreenSize(800, 500)
{

}

void Game::operator=(const Game &)
{
}


Game::~Game()
{
}

void Game::Initialize()
{
#ifdef _DEBUG
	DxLib::ChangeWindowMode(true);
#else
	int ans = MessageBox(nullptr, "フルスクリーンで表示しますか？", "画面の大きさどうしようか", MB_YESNO | MB_ICONQUESTION);

	if (ans == IDYES)
	{
		DxLib::ChangeWindowMode(false);
	}
	else
	{
		DxLib::ChangeWindowMode(true);
	}
#endif // DEBUG


	

	DxLib::SetGraphMode(ScreenSize.x, ScreenSize.y, 32);

	if (DxLib::DxLib_Init() == -1)
	{
		return;
	}

	DxLib::SetMainWindowText("Parasitism Shooting");	// タイトル
	DxLib::SetWindowIconID(IDI_ICON1);					// アイコン
	DxLib::SetDrawScreen(DX_SCREEN_BACK);				// 裏画面に描画

	ChangeScene(new TitleScene());
}

void Game::Run()
{
	Peripheral peripheral;

	while (DxLib::ProcessMessage() == 0)
	{
		DxLib::ClearDrawScreen();

		if (DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		peripheral.Update();

		scene->Update(peripheral);

		DxLib::ScreenFlip();
	}
}

void Game::Terminate()
{
	DxLib::DxLib_End();
}

void Game::ChangeScene(Scene* s)
{
	scene.reset(s);
}

const Vector2& Game::GetScreenSize()const
{
	return ScreenSize;
}
