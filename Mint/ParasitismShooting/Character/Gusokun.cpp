#include "Gusokun.h"
#include "../Game.h"
#include <DxLib.h>
#include "EnemyActionPattern.h"


Gusokun::Gusokun(const Player& player) : Enemy(player), player(player)
{
	ReadActionFile("action/boss.act");
	ChangeAction("eIdle");
	SetCharaSize(0.30f);
	charaData.ShotReady = false;
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());
	score = 200;

	eAction.reset(new EnemyActionPattern());

	updater = &Gusokun::Move;
}

Gusokun::Gusokun(const Gusokun& d) : Enemy(d.player), player(player)
{
	*this = d;
}

void Gusokun::operator=(const Gusokun& d)
{
	memcpy(this, &d, sizeof(Gusokun));
}

Enemy * Gusokun::Clone()
{
	return new Gusokun(*this);
}

void Gusokun::Move()
{
	if (charaData.ShotReady == true)
	{
		charaData.ShotReady = false;
	}
	//eAction->Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.ShotReady);
	cnt++;
}

void Gusokun::Die()
{
	scoreFlag = true;
	lifeFlag = false;
}

void Gusokun::Stunning()
{

	EnemyActionPattern eAction;
	eAction.Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.ShotReady);
	if (charaData.ShotReady == true)
	{
		charaData.ShotReady = false;
	}
}

void Gusokun::StunDamage()
{
	--charaData.SP;
	if (charaData.SP <= 0)
	{
		updater = &Gusokun::Stunning;
	}
}

Gusokun::~Gusokun()
{
}

void Gusokun::Update()
{
	//ProceedAnimationFile();

	(this->*updater)();
}

void Gusokun::Draw(int time)
{
	if (updater != &Gusokun::Stunning)
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

void Gusokun::Damage()
{
	charaData.HP -= 1;
	if (charaData.HP <= 0)
	{
		updater = &Gusokun::Die;
	}
}
