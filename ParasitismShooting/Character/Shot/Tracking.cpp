#include "Tracking.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

Tracking::Tracking(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot3");
	SetCharaSize(0.5f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &Tracking::Move;
}

Tracking::Tracking(const Tracking & d) : Shot(d.player, d.enemyfactory),player(player), enemyfactory(enemyfactory)
{
	*this = d;
}

void Tracking::operator=(const Tracking &d)
{
	memcpy(this, &d, sizeof(Tracking));
}

Shot * Tracking::Clone()
{
	return new Tracking(*this);
}

void Tracking::Move()
{
	if (shotst.shooter == SHOOTER::ENEMY)
	{
		if ((shotst.time % 60) == 0)
		{
			shotst.angle = SetTracking(shotst.shotType, pos, shotst.shooter, shotst.angle);
		}
	}
	else if (shotst.shooter == SHOOTER::PLAYER)
	{
		if ((shotst.time % 30) == 0)
		{
			shotst.angle = SetTracking(shotst.shotType, pos, shotst.shooter, shotst.angle);
		}
	}
	pos.x += cos(shotst.angle) * shotst.speed;
	pos.y += sin(shotst.angle) * shotst.speed;
	shotst.time++;
}

void Tracking::Delete()
{
	lifeFlag = false;
}

Tracking::~Tracking()
{
}

void Tracking::Update()
{
	(this->*updater)();
}

void Tracking::Draw()
{
	CharacterObject::Draw(charaData.img);
}
