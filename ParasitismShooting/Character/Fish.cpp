#include "Fish.h"
#include "../Game.h"
#include <DxLib.h>
#include "EnemyActionPattern.h"


Fish::Fish(const Player& player) : Enemy(player), player(player)
{
	ReadActionFile("action/fish.act");
	ChangeAction("Idle");
	SetCharaSize(0.07f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());
	
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
	eAction.ActPattern0(pos, charaData.moveVel, cnt, wait);
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
	--charaData.SP;
	if (charaData.SP <= 0)
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
		CharacterObject::Draw(charaData.img);
	}
	else
	{
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs((time*5 % 255) - 127) + 128);
		CharacterObject::Draw(charaData.img);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Fish::Damage()
{
	charaData.HP -= 1;
	if (charaData.HP <= 0)
	{
		updater = &Fish::Die;
	}
}
