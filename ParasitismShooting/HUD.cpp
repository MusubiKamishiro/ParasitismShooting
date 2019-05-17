#include "HUD.h"
#include "Game.h"
#include <DxLib.h>
#include <string>


HUD::HUD() : ssize(Game::Instance().GetScreenSize()), hudPos(Vector2(ssize.x - 300, 0))
{
	lifeColor = 0x0000ff;
	score = 0;
	upScore = 0;
	highScore = 2000;
}


HUD::~HUD()
{
}

void HUD::Update()
{
	if (upScore)
	{
		score += 10;
		upScore -= 10;
	}
}

void HUD::Draw(const int& life, const bool& flag)
{
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0xffffff, true);

	DxLib::DrawFormatString(510, 50, 0x000000, "最高得点　%012d", score > highScore ? score : highScore);
	DxLib::DrawFormatString(510, 80, 0x000000, "　　得点　%012d", score);

	//score+=10;


	// 寄生してるかどうかで色を分ける
	if (flag)
	{
		lifeColor = 0xff0000;
	}
	else
	{
		lifeColor = 0x0000ff;
	}

	DxLib::DrawString(515, 150, "HP", lifeColor);
	for (int a = 1; a < life; a++)
	{
		DxLib::DrawString(550 + a * 24, 150, "★", lifeColor);
	}
}

void HUD::AddScore(const unsigned int & inscore)
{
	upScore += inscore;
}

const Vector2 HUD::GetHUDPos()const
{
	return hudPos;
}
