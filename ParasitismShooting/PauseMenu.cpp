#include "PauseMenu.h"
#include <DxLib.h>


PauseMenu::PauseMenu()
{
	img = DxLib::LoadGraph("img/283logo.png");
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::Update()
{
}

void PauseMenu::Draw()
{
	DxLib::DrawExtendGraph(100, 100, 400, 400, img, true);
}
