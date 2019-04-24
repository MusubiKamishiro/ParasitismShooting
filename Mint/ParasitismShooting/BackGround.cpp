#include "BackGround.h"
#include <DxLib.h>
#include "GameScreen.h"
#include <string>

BackGround::BackGround()
{
	GameScreen gscreen;

	gssize = gscreen.GetGSSize();

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

	DxLib::DrawExtendGraph(-1, pos - 1, gssize.x, pos + gssize.y, BGimg, true);
	DxLib::DrawExtendGraph(-1, pos - gssize.y, gssize.x, pos - 1, BGimg, true);
}
