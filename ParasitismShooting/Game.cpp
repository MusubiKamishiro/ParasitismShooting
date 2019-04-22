#include "Game.h"
#include <DxLib.h>
#include "Peripheral.h"

#include "Scene/TitleScene.h"
//#include "resource.h"


Game::Game() : ScreenSize(600, 800)
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
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(ScreenSize.x, ScreenSize.y, 32);

	if (DxLib::DxLib_Init() == -1)
	{
		return;
	}

	DxLib::SetMainWindowText("Parasitism Shooting");		// �^�C�g��
	//DxLib::SetWindowIconID(IDI_ICON1);	// �A�C�R��
	DxLib::SetDrawScreen(DX_SCREEN_BACK);	// ����ʂɕ`��

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
