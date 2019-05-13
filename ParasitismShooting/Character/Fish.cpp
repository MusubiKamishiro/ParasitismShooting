#include "Fish.h"
#include "../Game.h"
#include <DxLib.h>
#include "EnemyActionPattern.h"


Fish::Fish(const Player& player) : Enemy(player), player(player)
{
	ReadActionFile("action/fish.act");
	ChangeAction("Idle");
	SetCharaSize(0.07f);
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());
	
	updater = &Fish::Move;
}

Fish::Fish(const Fish& d) : Enemy(d.player), player(player)
{
	*this = d;
}

void Fish::operator=(const Fish& d)
{
	memcpy(this, &d, sizeof(Fish));
}

Enemy * Fish::Clone()
{
	return new Fish(*this);
}

void Fish::Move()
{
	EnemyActionPattern eAction;
	eAction.ActPattern0(pos, 1.0f, cnt, wait);
	cnt++;
}

void Fish::Die()
{
	lifeFlag = false;
}

void Fish::Stunning()
{
	
}

void Fish::StunDamage()
{
	--SP;
	if (SP <= 0)
	{
		updater = &Fish::Stunning;
	}
}

Fish::~Fish()
{
}

void Fish::Update()
{
	//ProceedAnimationFile();

	(this->*updater)();
}

void Fish::Draw(int time)
{
	if (updater != &Fish::Stunning)
	{
		CharacterObject::Draw(img);
	}
	else
	{
		if ((time / 20) % 2)
		{
			DxLib::GraphFilter(img, DX_GRAPH_FILTER_INVERT);
			CharacterObject::Draw(img);
			DxLib::GraphFilter(img, DX_GRAPH_FILTER_INVERT);
		}
		else
		{
			CharacterObject::Draw(img);
		}
	}
}

void Fish::Damage()
{
	HP -= 1;
	if (HP <= 0)
	{
		updater = &Fish::Die;
	}
}
