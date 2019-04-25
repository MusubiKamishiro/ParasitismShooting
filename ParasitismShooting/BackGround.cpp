#include "BackGround.h"
#include <DxLib.h>
#include "GameScreen.h"
#include <string>

BackGround::BackGround()
{
	gs.reset(new GameScreen());
	gssize = gs->GetGSSize();
	
	std::string s;
	//s += "img/bg" + std::to_string(0) + ".png";
	s = "img/bg.png";

	BGimg = DxLib::LoadGraph(s.c_str());
}


BackGround::~BackGround()
{
}

void BackGround::Draw(const int& time)
{
	int pos = (time * 2) % (int)gssize.y;

	DxLib::DrawExtendGraph(gs->outscreen, pos, gssize.x, pos + gssize.y, BGimg, true);
	DxLib::DrawExtendGraph(gs->outscreen, pos - gssize.y, gssize.x, pos, BGimg, true);
}
