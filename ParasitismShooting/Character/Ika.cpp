#include "Ika.h"
#include "../Game.h"
#include <DxLib.h>
#include "EnemyActionPattern.h"


Ika::Ika(const Player& player) : Enemy(player), player(player)
{
	ReadActionFile("action/squid.act");
	ChangeAction("Idle");
	SetCharaSize(0.07f);
	charaData.shotReady = false;
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());
	score = 200;

	actFlag = true;
	eAction.reset(new EnemyActionPattern());

	updater = &Ika::Move;
}

Ika::Ika(const Ika& d) : Enemy(d.player), player(player)
{
	*this = d;
}

void Ika::operator=(const Ika& d)
{
	memcpy(this, &d, sizeof(Ika));
}

Enemy * Ika::Clone()
{
	return new Ika(*this);
}

void Ika::Move()
{
	if (charaData.shotReady == true)
	{
		charaData.shotReady = false;
	}

	eAction->Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.shotReady);
	cnt++;
}

void Ika::Die()
{
	scoreFlag = true;
	lifeFlag = false;
	actFlag = false;
}

void Ika::Stunning()
{
	eAction->Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.shotReady);
	if (charaData.shotReady == true)
	{
		charaData.shotReady = false;
	}
}

void Ika::StunDamage()
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
		updater = &Ika::Stunning;
	}
}

Ika::~Ika()
{
}

void Ika::Update()
{
	//ProceedAnimationFile();

	(this->*updater)();
}

void Ika::Draw(int time)
{
	if (updater != &Ika::Stunning)
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

void Ika::Damage()
{
	charaData.HP -= 1;
	if (charaData.HP <= 0)
	{
		updater = &Ika::Die;
	}
}
