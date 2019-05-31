#include "Shotgun.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

Shotgun::Shotgun(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot2");
	SetCharaSize(0.3f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &Shotgun::Move;
}

Shotgun::Shotgun(const Shotgun & d) : Shot(d.player, d.enemyfactory),player(player), enemyfactory(enemyfactory)
{
	*this = d;
}

void Shotgun::operator=(const Shotgun &d)
{
	memcpy(this, &d, sizeof(Shotgun));
}

Shot * Shotgun::Clone()
{
	return new Shotgun(*this);
}

void Shotgun::Move()
{
	pos.x += cos(shotst.angle) * shotst.speed;
	pos.y += sin(shotst.angle) * shotst.speed;
}

void Shotgun::Delete()
{
	lifeFlag = false;
}

Shotgun::~Shotgun()
{
}

void Shotgun::Update()
{
	(this->*updater)();
}

void Shotgun::Draw()
{
	CharacterObject::Draw(charaData.img);
}
