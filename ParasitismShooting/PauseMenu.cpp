#include "PauseMenu.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "GameScreen.h"


PauseMenu::PauseMenu()
{
	gs.reset(new GameScreen());

	ssize = gs->GetGSSize();

	pause = "ˆêŽž’âŽ~’†";
	resume = "ƒQ[ƒ€‚ð‘±‚¯‚é";
	end = "ƒ^ƒCƒgƒ‹‚É–ß‚é";
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
	DxLib::DrawString(GetStringPosx(pause), (ssize.y + gs->outscreen) / 3, pause.c_str(), 0xff00ff);
	DxLib::DrawString(GetStringPosx(resume), (ssize.y + gs->outscreen) / 3 + 100, resume.c_str(), 0xff00ff);
	DxLib::DrawString(GetStringPosx(end), (ssize.y + gs->outscreen) / 3 + 130, end.c_str(), 0xff00ff);
}

int PauseMenu::GetStringPosx(const std::string & name)
{
	return ((ssize.x + gs->outscreen) / 2 - DxLib::GetDrawStringWidth(name.c_str(), std::strlen(name.c_str())) / 2);
}
