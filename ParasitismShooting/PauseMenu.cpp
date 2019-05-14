#include "PauseMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "GameScreen.h"

PauseMenu::PauseMenu()
{
	gs.reset(new GameScreen());

	ssize = gs->GetGSSize();

	pause = "ˆê’â~’†";
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
	DxLib::DrawString(ssize.x / 2 + gs->outscreen / 2 - DxLib::GetDrawStringWidth(pause.c_str(), std::strlen(pause.c_str())) / 2, 
						ssize.y / 2 + gs->outscreen / 2, pause.c_str(), 0xff00ff);
}
