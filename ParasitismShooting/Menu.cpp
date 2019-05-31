#include "Menu.h"
#include <DxLib.h>
#include "GameScreen.h"
#include "Peripheral.h"
#include "KeyConfig.h"
#include "Sound.h"


Menu::Menu()
{
	gs.reset(new GameScreen());
	ssize = gs->GetGSSize();

	menuTitle.resize(0);
	menudata.resize(0);
	menuDescription.resize(0);
	selcnt = 0;

	decideFlag = false;

	Sound::Instance().AddSE("select.mp3");
}


Menu::~Menu()
{
}

void Menu::Update(const Peripheral & p)
{
	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(UP)))
	{
		Sound::Instance().PlaySE("select");
		--selcnt;
		if (selcnt < 0)
		{
			selcnt = menudata.size() - 1;
		}
	}
	if (p.IsTrigger(KeyConfig::Instance().GetNowKey(DOWN)))
	{
		Sound::Instance().PlaySE("select");
		++selcnt;
		if (selcnt > menudata.size() - 1)
		{
			selcnt = 0;
		}
	}
}

void Menu::Draw(const Vector2 & shiftpos)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
	for (auto& m : menuTitle)
	{
		DxLib::DrawString(m.pos.x + shiftpos.x, m.pos.y + shiftpos.y, m.name, m.color);
	}
	for (auto& m : menudata)
	{
		DxLib::DrawString(m.pos.x + shiftpos.x, m.pos.y + shiftpos.y, m.name, m.color);
	}
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	for (auto& m : menuTitle)
	{
		DxLib::DrawString(m.pos.x, m.pos.y, m.name, m.color);
	}
	for (int i = 0; i < menudata.size(); i++)
	{
		auto m = menudata.at(i);
		if (selcnt == i)
		{
			DxLib::DrawString(m.pos.x, m.pos.y, m.name, m.color);
		}
	}
}

int Menu::GetStringCenterPosx(const std::string & name)
{
	return ((ssize.x + gs->outscreen) / 2 - DxLib::GetDrawStringWidth(name.c_str(), std::strlen(name.c_str())) / 2);
}

int Menu::GetStringRightPosx(const std::string & name, const int& rpos)
{
	return (rpos - DxLib::GetDrawStringWidth(name.c_str(), std::strlen(name.c_str())));
}
