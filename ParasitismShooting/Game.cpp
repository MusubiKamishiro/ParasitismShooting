#include "Game.h"
#include <DxLib.h>
#include <random>
#include "Peripheral.h"
#include "Credit.h"

#include "Scene/TitleScene.h"
#include "resource.h"


Game::Game() : ScreenSize(800, 500)
{
	time = fps = count = oldcount = 0.0;
	oldEnter = enter = 0;
	fontSize = 24;
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
	DxLib::SetFontSize(fontSize);
	
	coinSound = DxLib::LoadSoundMem("sound/tirin1.mp3");

	ChangeScene(new TitleScene());
}

void Game::Run()
{
	Peripheral peripheral;
	Credit credit;

	while (DxLib::ProcessMessage() == 0)
	{
		++time;
		DxLib::ClearDrawScreen();

		if (DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		oldEnter = enter;
		enter = DxLib::CheckHitKey(KEY_INPUT_RETURN);
		if (enter && !oldEnter)
		{
			DxLib::PlaySoundMem(coinSound, DX_PLAYTYPE_BACK);
			credit.AddCredit();
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

		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());
		int edge = 5;
		for (int y = 0; y < ScreenSize.y; y += edge)
		{
			for (int x = 0; x < ScreenSize.x; x += edge)
			{
				/*if (engine() % 2 == 0)
				{
					DxLib::DrawBox(x, y, x + edge, y + edge, 0xffffff, true);
				}
				else
				{
					DxLib::DrawBox(x, y, x + edge, y + edge, 0x000000, true);
				}*/
				DxLib::DrawBox(x, y, x + edge, y + edge, engine() % 0xffffff, true);
			}
		}

		//if (engine() % 2 == 0)
		//{
		//	DxLib::DrawBox(0, 0, ScreenSize.x, ScreenSize.y, 0xff0000, true);
		//}
		//else
		//{
		//	DxLib::DrawBox(0, 0, ScreenSize.x, ScreenSize.y, 0x0000ff, true);
		//}

		// fps, クレジット表示
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DxLib::DrawFormatString(ScreenSize.x - 100, ScreenSize.y - fontSize, 0xff00ff, "%.2f fps", fps);
		credit.Draw();
		
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


