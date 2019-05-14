#include "Menu.h"
#include <DxLib.h>
#include "GameScreen.h"
#include "Peripheral.h"



Menu::Menu()
{
	gs.reset(new GameScreen());
	ssize = gs->GetGSSize();

	menuTitle = {};
	menudata.resize(0);
	selcnt = 0;
}


Menu::~Menu()
{
}

void Menu::Update(const Peripheral & p)
{
	if (p.IsTrigger(PAD_INPUT_UP))
	{
		--selcnt;
		if (selcnt < 0)
		{
			selcnt = menudata.size() - 1;
		}
	}
	if (p.IsTrigger(PAD_INPUT_DOWN))
	{
		++selcnt;
		if (selcnt > menudata.size() - 1)
		{
			selcnt = 0;
		}
	}
}

void Menu::Draw(const Vector2 & shiftpos, const unsigned int & color)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
	DxLib::DrawString(menuTitle.pos.x + shiftpos.x, menuTitle.pos.y + shiftpos.y, menuTitle.name, menuTitle.color);
	for (auto& m : menudata)
	{
		DxLib::DrawString(m.pos.x + shiftpos.x, m.pos.y + shiftpos.y, m.name, m.color);
	}
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DxLib::DrawString(menuTitle.pos.x, menuTitle.pos.y, menuTitle.name, menuTitle.color);
	for (int i = 0; i < menudata.size(); i++)
	{
		auto m = menudata.at(i);
		if ((selcnt) == i)
		{
			DxLib::DrawString(m.pos.x + shiftpos.x, m.pos.y + shiftpos.y, m.name, color);
		}
		else
		{
			DxLib::DrawString(m.pos.x, m.pos.y, m.name, m.color);
		}
	}
}

int Menu::GetStringPosx(const std::string & name)
{
	return ((ssize.x + gs->outscreen) / 2 - DxLib::GetDrawStringWidth(name.c_str(), std::strlen(name.c_str())) / 2);
}
