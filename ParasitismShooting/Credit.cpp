#include "Credit.h"
#include <string>
#include <DxLib.h>
#include "Game.h"


Credit::Credit() : ssize(Game::Instance().GetScreenSize())
{
	credit = 0;
}


Credit::~Credit()
{
}

void Credit::AddCredit()
{
	++credit;
}

void Credit::SubCredit()
{
	--credit;
}

unsigned int Credit::GetCredit() const
{
	return credit;
}

void Credit::Draw()
{
	std::string s  = "CREDITÅF" + std::to_string(credit);
	DxLib::DrawString(510, ssize.y - 30, s.c_str(), 0x0000ff);
}
