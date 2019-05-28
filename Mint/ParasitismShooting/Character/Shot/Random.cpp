#include "Random.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

Random::Random(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot6");
	SetCharaSize(0.5f);
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
	shotst.speed = 8 / 3;
	if (shotst.time == 60)
	{
		shotst.angle = GetAtan2(shotst.shooter,shotst.angle);
	}
	pos.x += cos(shotst.angle) * (float)shotst.speed;
	pos.y += sin(shotst.angle) * (float)shotst.speed;

	shotst.time++;
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
