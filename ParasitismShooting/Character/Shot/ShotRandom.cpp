#include "ShotRandom.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

ShotRandom::ShotRandom(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot5");
	SetCharaSize(0.5f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &ShotRandom::Move;
}

ShotRandom::ShotRandom(const ShotRandom & d) : Shot(d.player, d.enemyfactory),player(player), enemyfactory(enemyfactory)
{
	*this = d;
}

void ShotRandom::operator=(const ShotRandom &d)
{
	memcpy(this, &d, sizeof(ShotRandom));
}

Shot * ShotRandom::Clone()
{
	return new ShotRandom(*this);
}

void ShotRandom::Move()
{
	pos.x += cos(shotst.angle) * shotst.speed;
	pos.y += sin(shotst.angle) * shotst.speed;
}

void ShotRandom::Delete()
{
	lifeFlag = false;
}

ShotRandom::~ShotRandom()
{
}

void ShotRandom::Update()
{
	(this->*updater)();
}

void ShotRandom::Draw()
{
	CharacterObject::Draw(charaData.img);
}
