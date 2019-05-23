#include "HUD.h"
#include "Game.h"
#include <DxLib.h>
#include <string>


HUD::HUD() : ssize(Game::Instance().GetScreenSize()), hudPos(Vector2(ssize.x - 300, 0))
{
	lifeColor = 0x0000ff;
	score = 0;
	upScore = 0;
	highScore = 5000;
	cCount = 0;
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
	
	/*DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 32);
	DxLib::DrawBox(510, 10, ssize.x - 10, ssize.y - 10, 0x000000, true);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);*/

	DxLib::DrawFormatString(510, 50, 0x000000, "最高得点　%012d", score > highScore ? score : highScore);
	DxLib::DrawFormatString(510, 80, 0x000000, "　　得点　%012d", score);


	// 寄生してるかどうかでHPの色を分ける
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

	DxLib::DrawFormatString(510, 250, 0x000000, "コンティニュー回数　%02d", cCount);
}

void HUD::AddScore(const unsigned int & inscore)
{
	upScore += inscore;
}

void HUD::InitScore()
{
	highScore = score > highScore ? score : highScore;
	score = 0;
	upScore = 0;
}

void HUD::AddContinueCount()
{
	++cCount;
}

const Vector2 HUD::GetHUDPos()const
{
	return hudPos;
}

unsigned int HUD::GetScore() const
{
	return score;
}

unsigned int HUD::GetContinueCount() const
{
	return cCount;
}
