#include "Boss.h"
#include "../Game.h"
#include <DxLib.h>
#include "EnemyActionPattern.h"


Boss::Boss(const Player& player) : Enemy(player), player(player)
{
	ReadActionFile("action/boss.act");
	ChangeAction("Idle");
	SetCharaSize(0.30f);
	charaData.ShotReady = false;
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());
	score = 200;

	updater = &Boss::Move;
}

Boss::Boss(const Boss& d) : Enemy(d.player), player(player)
{
	*this = d;
}

void Boss::operator=(const Boss& d)
{
	memcpy(this, &d, sizeof(Boss));
}

Enemy * Boss::Clone()
{
	return new Boss(*this);
}

void Boss::Move()
{
	if (charaData.ShotReady == true)
	{
		charaData.ShotReady = false;
	}
	EnemyActionPattern eAction;
	eAction.Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.ShotReady);
	cnt++;
}

void Boss::Die()
{
	scoreFlag = true;
	lifeFlag = false;
}

void Boss::Stunning()
{

	EnemyActionPattern eAction;
	eAction.Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.ShotReady);
	if (charaData.ShotReady == true)
	{
		charaData.ShotReady = false;
	}
}

void Boss::StunDamage()
{
	--charaData.SP;
	if (charaData.SP <= 0)
	{
		updater = &Boss::Stunning;
	}
}

Boss::~Boss()
{
}

void Boss::Update()
{
	//ProceedAnimationFile();

	(this->*updater)();
}

void Boss::Draw(int time)
{
	if (updater != &Boss::Stunning)
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

void Boss::Damage()
{
	charaData.HP -= 1;
	if (charaData.HP <= 0)
	{
		updater = &Boss::Die;
	}
}
