#include "Shot.h"
#include <DxLib.h>


Shot::Shot()
{
	DxLib::LoadDivGraph("img/lightbullet.png", 8, 8, 1, 60, 60, img, true);
}


Shot::~Shot()
{
}

void Shot::Update(void)
{
	Draw();
}

void Shot::Draw(void)
{
	DxLib::DrawGraph(50, 50, img[0], true);
}
