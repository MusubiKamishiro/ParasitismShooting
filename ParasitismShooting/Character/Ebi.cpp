#include "Ebi.h"
#include "../Game.h"
#include <DxLib.h>
#include "EnemyActionPattern.h"


Ebi::Ebi(const Player& player) : Enemy(player), player(player)
{
	ReadActionFile("action/shrimp.act");
	ChangeAction("eIdle");
	SetCharaSize(0.07f);
	charaData.shotReady = false;
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());
	score = 200;

	actFlag = true;
	eAction.reset(new EnemyActionPattern());

	updater = &Ebi::Move;
}

Ebi::Ebi(const Ebi& d) : Enemy(d.player), player(player)
{
	*this = d;
}

void Ebi::operator=(const Ebi& d)
{
	memcpy(this, &d, sizeof(Ebi));
}

Enemy * Ebi::Clone()
{
	return new Ebi(*this);
}

void Ebi::Move()
{
	if (charaData.shotReady == true)
	{
		charaData.shotReady = false;
	}

	eAction->Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.shotReady);
	cnt++;
}

void Ebi::Die()
{
	scoreFlag = true;
	lifeFlag = false;
	actFlag = false;
}

void Ebi::Stunning()
{
	eAction->Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.shotReady);
	if (charaData.shotReady == true)
	{
		charaData.shotReady = false;
	}
}

void Ebi::StunDamage()
{
	--charaData.SP;
	if (charaData.SP <= 0)
	{
		if (charaData.shotType == "WeakNormal")
		{
			charaData.shotType = "Normal";
		}
		else if (charaData.shotType == "WeakShotgun")
		{
			charaData.shotType = "Shotgun";
		}
		updater = &Ebi::Stunning;
	}
}

Ebi::~Ebi()
{
}

void Ebi::Update()
{
	//ProceedAnimationFile();

	(this->*updater)();
}

void Ebi::Draw(int time)
{
	if (updater != &Ebi::Stunning)
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

void Ebi::Damage()
{
	charaData.HP -= 1;
	if (charaData.HP <= 0)
	{
		updater = &Ebi::Die;
	}
}
