#include "Fish.h"
#include "../Game.h"
#include <DxLib.h>
#include "EnemyActionPattern.h"


Fish::Fish(const Player& player) : Enemy(player), player(player)
{
	ReadActionFile("action/fish.act");
	ChangeAction("Idle");
	SetCharaSize(0.07f);
	charaData.ShotReady = false;
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
	if (charaData.ShotReady == true)
	{
		charaData.ShotReady = false;
	}
	EnemyActionPattern eAction;
	eAction.Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.ShotReady);
	cnt++;
}

void Fish::Die()
{
	lifeFlag = false;
}

void Fish::Stunning()
{
	EnemyActionPattern eAction;
	eAction.Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.ShotReady);
}

void Fish::StunDamage()
{
	--charaData.SP;
	if (charaData.SP <= 0)
	{
		if (charaData.ShotReady == true)
		{
			charaData.ShotReady = false;
		}
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
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs((time * 5 % 255) - 127) + 128);
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
