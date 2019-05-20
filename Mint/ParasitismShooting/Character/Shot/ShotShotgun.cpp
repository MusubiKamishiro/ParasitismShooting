#include "ShotShotgun.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

ShotShotgun::ShotShotgun(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot2");
	SetCharaSize(0.5f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &ShotShotgun::Move;
}

ShotShotgun::ShotShotgun(const ShotShotgun & d) : Shot(d.player, d.enemyfactory),player(player), enemyfactory(enemyfactory)
{
	*this = d;
}

void ShotShotgun::operator=(const ShotShotgun &d)
{
	memcpy(this, &d, sizeof(ShotShotgun));
}

Shot * ShotShotgun::Clone()
{
	return new ShotShotgun(*this);
}

void ShotShotgun::Move()
{
	pos.x += cos(shotst.angle) * shotst.speed;
	pos.y += sin(shotst.angle) * shotst.speed;
}

void ShotShotgun::Delete()
{
	lifeFlag = false;
}

ShotShotgun::~ShotShotgun()
{
}

void ShotShotgun::Update()
{
	(this->*updater)();
}

void ShotShotgun::Draw()
{
	CharacterObject::Draw(charaData.img);
}
