#include "Random.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

Random::Random(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot5");
	SetCharaSize(0.3f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &Random::Move;
}

Random::Random(const Random & d) : Shot(d.player, d.enemyfactory),player(player), enemyfactory(enemyfactory)
{
	*this = d;
}

void Random::operator=(const Random &d)
{
	memcpy(this, &d, sizeof(Random));
}

Shot * Random::Clone()
{
	return new Random(*this);
}

void Random::Move()
{
	pos.x += cos(shotst.angle) * shotst.speed;
	pos.y += sin(shotst.angle) * shotst.speed;
}

void Random::Delete()
{
	lifeFlag = false;
}

Random::~Random()
{
}

void Random::Update()
{
	(this->*updater)();
}

void Random::Draw()
{
	CharacterObject::Draw(charaData.img);
}
