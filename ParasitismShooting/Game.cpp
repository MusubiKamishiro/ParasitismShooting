#include "Game.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Scene/SceneManager.h"
#include "Sound.h"
#include "resource.h"
#include "FrameFixity.h"


Game::Game() : ScreenSize(800, 500)
{
	time = fps = count = oldcount = 0.0;
	fontSize = 24;
}

void Game::operator=(const Game &)
{
}

void Game::DrawFps()
{
	count = DxLib::GetNowCount();
	if ((count - oldcount) > 1000)
	{
		fps = ((time * 1000) / (count - oldcount));
		oldcount = count;
		time = 0;
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DxLib::DrawFormatString(ScreenSize.x - 100, ScreenSize.y - fontSize, 0xff00ff, "%.2f fps", fps);
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
	DxLib::SetFontSize(fontSize);
}

void Game::Run()
{
	Peripheral peripheral;
	auto& scenes = SceneManager::Instance();
	FrameFixity& ff = FrameFixity::Instance();
	ff.FFInitialize();

	while (DxLib::ProcessMessage() == 0)
	{
		if (ff.CheckReceiveMessage()) {
			if (ff.GetReceiveMessage().message == WM_QUIT) {
				break;
			}
		}
		else {
			ff.AdjustmentFrameLate();

			++time;
			DxLib::ClearDrawScreen();

			// エスケープキーで終了
			if (DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}

			peripheral.Update();
			scenes.Update(peripheral);
			scenes.Draw();

			DrawFps();

			DxLib::ScreenFlip();
		}
	}

	ff.Terminate();
}

void Game::Terminate()
{
	Sound::Instance().DeleteSoundAll();
	DxLib::DxLib_End();
}

const Vector2& Game::GetScreenSize()const
{
	return ScreenSize;
}


