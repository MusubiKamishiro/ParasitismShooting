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
	int posy = (time * 2) % (int)gssize.y;

	DxLib::DrawExtendGraph(0, posy, gssize.x + gs->outscreen, posy + gssize.y, BGimg, true);
	DxLib::DrawExtendGraph(0, posy - gssize.y, gssize.x + gs->outscreen, posy, BGimg, true);
	DxLib::DrawExtendGraph(0, posy + gssize.y, gssize.x + gs->outscreen, posy + gssize.y*2, BGimg, true);
}
