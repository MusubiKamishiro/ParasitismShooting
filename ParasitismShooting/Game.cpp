#include "Game.h"
#include <DxLib.h>
#include <string>
#include "Peripheral.h"

#include "Scene/TitleScene.h"
#include "resource.h"


Game::Game() : ScreenSize(800, 500)
{
	time = fps = count = oldcount = 0.0;
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
	int ans = MessageBox(DxLib::GetMainWindowHandle(), "フルスクリーンで表示しますか？", "画面の大きさどうしようか", MB_YESNO | MB_ICONQUESTION);

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

	AddFontResourceEx("Ronde-B_square.otf", FR_PRIVATE, nullptr);
	
	DxLib::ChangeFont("ロンド B スクエア", DX_CHARSET_DEFAULT);
	DxLib::SetFontSize(24);

	ChangeScene(new TitleScene());
}

void Game::Run()
{
	Peripheral peripheral;

	while (DxLib::ProcessMessage() == 0)
	{
		++time;
		DxLib::ClearDrawScreen();

		if (DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		peripheral.Update();

		scene->Update(peripheral);

		count = DxLib::GetNowCount();

		if ((count - oldcount) > 1000)
		{
			fps = ((time * 1000) / (count - oldcount));
			oldcount = count;
			time = 0;
		}

		std::string s = "fps：" + std::to_string(fps);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DxLib::DrawString(0, 0, s.c_str(), 0xff00ff);
		
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


