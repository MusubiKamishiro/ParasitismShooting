#include "PauseMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "GameScreen.h"

PauseMenu::PauseMenu()
{
	img = DxLib::LoadGraph("img/283logo.png");
	gs.reset(new GameScreen());

	ssize = gs->GetGSSize();
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::Update(const Peripheral& p)
{
	if(p.IsTrigger(PAD_INPUT_UP))
	{

	}
	if (p.IsTrigger(PAD_INPUT_DOWN))
	{

	}
	if (p.IsTrigger(PAD_INPUT_2))
	{

	}
}

void PauseMenu::Draw()
{
	//DxLib::DrawExtendGraph(100, 100, 400, 400, img, true);

	DxLib::DrawString(gs->outscreen, gs->outscreen, "break", 0xff00ff);
}
