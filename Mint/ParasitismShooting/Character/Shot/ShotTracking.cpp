#include "ShotTracking.h"
#include "../../Game.h"
#include "../Enemy.h"
#include <DxLib.h>

ShotTracking::ShotTracking(const Player& player/*, const Enemy& enemy*/) : Shot(player/*, enemy*/),player(player), enemy(enemy)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot3");
	SetCharaSize(0.5f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &ShotTracking::Move;
}

ShotTracking::ShotTracking(const ShotTracking & d) : Shot(d.player/*, d.enemy*/),player(player), enemy(enemy)
{
	*this = d;
}

void ShotTracking::operator=(const ShotTracking &d)
{
	memcpy(this, &d, sizeof(ShotTracking));
}

Shot * ShotTracking::Clone()
{
	return new ShotTracking(*this);
}

void ShotTracking::Move()
{
	pos.x += cos(angle) * Speed;
	pos.y += sin(angle) * Speed;
}

void ShotTracking::Delete()
{
	lifeFlag = false;
}

ShotTracking::~ShotTracking()
{
}

void ShotTracking::Update()
{
	(this->*updater)();
}

void ShotTracking::Draw()
{
	CharacterObject::Draw(charaData.img);
}