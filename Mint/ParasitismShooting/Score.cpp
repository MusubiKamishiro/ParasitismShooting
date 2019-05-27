#include "Score.h"
#include <DxLib.h>


Score::Score()
{
	nowScore = 0;
	upScore = 0;
	highScore = 5000;
	cCount = 0;
}

void Score::operator=(const Score &)
{
}


Score::~Score()
{
}

void Score::Update()
{
	if (upScore)
	{
		nowScore += 10;
		upScore -= 10;
	}
}

void Score::Draw(const Vector2& pos)
{
	DxLib::DrawFormatString(pos.x, pos.y,		0x000000, "最高得点　%012d", nowScore > highScore ? nowScore : highScore);
	DxLib::DrawFormatString(pos.x, pos.y + 30,	0x000000, "　　得点　%012d", nowScore);

	DxLib::DrawFormatString(pos.x, pos.y + 200, 0x000000, "コンティニュー回数　%02d", cCount);
}

void Score::InitScore(const bool& flag)
{
	highScore = nowScore > highScore ? nowScore : highScore;
	nowScore = 0;
	upScore = 0;

	if (flag)
	{
		cCount = 0;
	}
}

void Score::AddScore(const unsigned int & inscore)
{
	upScore += inscore;
}

void Score::AddContinueCount()
{
	++cCount;
}

unsigned int Score::GetNowScore() const
{
	return nowScore;
}

unsigned int Score::GetHighScore() const
{
	return highScore;
}

unsigned int Score::GetContinueCount() const
{
	return cCount;
}
