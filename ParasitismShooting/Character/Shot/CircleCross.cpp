#include "CircleCross.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

CircleCross::CircleCross(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot6");
	SetCharaSize(0.3f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &CircleCross::Move;
}

CircleCross::CircleCross(const CircleCross & d) : Shot(d.player, d.enemyfactory),player(player), enemyfactory(enemyfactory)
{
	*this = d;
}

void CircleCross::operator=(const CircleCross &d)
{
	memcpy(this, &d, sizeof(CircleCross));
}

Shot * CircleCross::Clone()
{
	return new CircleCross(*this);
}

void CircleCross::Move()
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

void CircleCross::Delete()
{
	lifeFlag = false;
}

CircleCross::~CircleCross()
{
}

void CircleCross::Update()
{
	(this->*updater)();
}

void CircleCross::Draw()
{
	CharacterObject::Draw(charaData.img);
}
