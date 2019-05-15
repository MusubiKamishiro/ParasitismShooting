#include "Game.h"
#include <DxLib.h>
#include <string>
#include "Peripheral.h"
#include "Credit.h"

#include "Scene/TitleScene.h"
#include "resource.h"


Game::Game() : ScreenSize(800, 500)
{
	time = fps = count = oldcount = 0.0;
	oldEnter = enter = 0;
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
	int ans = MessageBox(DxLib::GetMainWindowHandle(), "�t���X�N���[���ŕ\�����܂����H", "��ʂ̑傫���ǂ����悤��", MB_YESNO | MB_ICONQUESTION);

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

	DxLib::SetMainWindowText("Parasitism Shooting");	// �^�C�g��
	DxLib::SetWindowIconID(IDI_ICON1);					// �A�C�R��
	DxLib::SetDrawScreen(DX_SCREEN_BACK);				// ����ʂɕ`��

	AddFontResourceEx("Ronde-B_square.otf", FR_PRIVATE, nullptr);
	DxLib::ChangeFont("�����h B �X�N�G�A", DX_CHARSET_DEFAULT);
	DxLib::SetFontSize(24);
	
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

		// fps, �N���W�b�g�\��
		std::string s = "fps�F" + std::to_string(fps);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DxLib::DrawString(0, 0, s.c_str(), 0xff00ff);

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


