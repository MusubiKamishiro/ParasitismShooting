#include "Weak.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

Weak::Weak(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot5");
	SetCharaSize(0.3f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &Weak::Move;
}

Weak::Weak(const Weak & d) : Shot(d.player, d.enemyfactory),player(player), enemyfactory(enemyfactory)
{
	*this = d;
}

void Weak::operator=(const Weak &d)
{
	memcpy(this, &d, sizeof(Weak));
}

Shot * Weak::Clone()
{
	return new Weak(*this);
}

void Weak::Move()
{
	pos.x += cos(shotst.angle) * shotst.speed;
	pos.y += sin(shotst.angle) * shotst.speed;
}

void Weak::Delete()
{
	lifeFlag = false;
}

Weak::~Weak()
{
}

void Weak::Update()
{
	(this->*updater)();
}

void Weak::Draw()
{
	CharacterObject::Draw(charaData.img);
}
