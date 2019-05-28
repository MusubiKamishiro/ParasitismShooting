#include "Normal.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

Normal::Normal(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot1");
	SetCharaSize(0.5f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &Normal::Move;
}

Normal::Normal(const Normal & d) : Shot(d.player, d.enemyfactory),player(player), enemyfactory(enemyfactory)
{
	*this = d;
}

void Normal::operator=(const Normal &d)
{
	memcpy(this, &d, sizeof(Normal));
}

Shot * Normal::Clone()
{
	return new Normal(*this);
}

void Normal::Move()
{
	pos.x += cos(shotst.angle) * shotst.speed;
	pos.y += sin(shotst.angle) * shotst.speed;
}

void Normal::Delete()
{
	lifeFlag = false;
}

Normal::~Normal()
{
}

void Normal::Update()
{
	(this->*updater)();
}

void Normal::Draw()
{
	CharacterObject::Draw(charaData.img);
}
