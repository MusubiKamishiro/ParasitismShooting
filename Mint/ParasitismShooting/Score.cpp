#include "Score.h"
#include <DxLib.h>


Score::Score()
{
	nowScore = 0;
	upScore = 0;
	highScore = 5000;

	stageBonus = 0;
	parasBonus = 0;
	bossHpBonus = 0;
	contBonus = 0;
	diffBonus = 0.0f;
	bonusScore = 0;
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

	if (upScore > 1000)
	{
		nowScore += 270;
		upScore -= 270;
	}
}

void Score::Draw(const Vector2& pos)
{
	DxLib::DrawFormatString(pos.x, pos.y,		0x000000, "最高得点　%012d", nowScore > highScore ? nowScore : highScore);
	DxLib::DrawFormatString(pos.x, pos.y + 30,	0x000000, "　　得点　%012d", nowScore);
}

void Score::InitScore()
{
	highScore = nowScore > highScore ? nowScore : highScore;
	nowScore = 0;
	upScore = 0;
}

void Score::AddScore(const unsigned int & inscore)
{
	upScore += inscore;
}

void Score::AddClearBonus(const unsigned int& stagenum, const unsigned int& parasnum, const int& bosshp, const unsigned int& ccount, const int& diff)
{
	stageBonus = stagenum * 1000;
	parasBonus = parasnum * 10;
	bossHpBonus = bosshp * 100;
	contBonus = ccount * -1000;
	diffBonus = 0.5 * (diff + 1);

	bonusScore = stageBonus + parasBonus + bossHpBonus + contBonus;
	bonusScore *= diffBonus;

	if (bonusScore <= 0)
	{
		bonusScore = 0;
	}
	upScore += bonusScore;
}

unsigned int Score::GetNowScore() const
{
	return nowScore;
}

unsigned int Score::GetHighScore() const
{
	return highScore;
}

