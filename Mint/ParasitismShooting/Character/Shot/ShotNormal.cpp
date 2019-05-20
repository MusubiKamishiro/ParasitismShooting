#include "ShotNormal.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

ShotNormal::ShotNormal(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot1");
	SetCharaSize(0.5f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &ShotNormal::Move;
}

ShotNormal::ShotNormal(const ShotNormal & d) : Shot(d.player, d.enemyfactory),player(player), enemyfactory(enemyfactory)
{
	*this = d;
}

void ShotNormal::operator=(const ShotNormal &d)
{
	memcpy(this, &d, sizeof(ShotNormal));
}

Shot * ShotNormal::Clone()
{
	return new ShotNormal(*this);
}

void ShotNormal::Move()
{
	pos.x += cos(shotst.angle) * shotst.speed;
	pos.y += sin(shotst.angle) * shotst.speed;
}

void ShotNormal::Delete()
{
	lifeFlag = false;
}

ShotNormal::~ShotNormal()
{
}

void ShotNormal::Update()
{
	(this->*updater)();
}

void ShotNormal::Draw()
{
	CharacterObject::Draw(charaData.img);
}
