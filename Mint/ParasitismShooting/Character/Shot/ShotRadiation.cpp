#include "ShotRadiation.h"
#include "../../Game.h"
#include "../EnemyFactory.h"
#include <DxLib.h>

ShotRadiation::ShotRadiation(const Player& player, const EnemyFactory& enemyfactory) : Shot(player, enemyfactory),player(player), enemyfactory(enemyfactory)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot4");
	SetCharaSize(0.5f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());
	range = 30.0f;
	updater = &ShotRadiation::Move;
}

ShotRadiation::ShotRadiation(const ShotRadiation & d) : Shot(d.player, d.enemyfactory),player(player), enemyfactory(enemyfactory)
{
	*this = d;
}

void ShotRadiation::operator=(const ShotRadiation &d)
{
	memcpy(this, &d, sizeof(ShotRadiation));
}

Shot * ShotRadiation::Clone()
{
	return new ShotRadiation(*this);
}

void ShotRadiation::Move()
{
	//shotst.angle = range / 180.0f;
	if (shotst.time % 3 == 0)
	{
		shotst.angle += range / 180.0f;
	}
	if (shotst.shooter == SHOOTER::PLAYER)
	{
		shotst.speed = 3;
	}
	if (shotst.time > 300)
	{
		lifeFlag = false;
	}
	pos.x += cos(shotst.angle) * shotst.speed;
	pos.y += sin(shotst.angle) * shotst.speed;

	shotst.time++;

	//rotation2D(&pos.x, &pos.y, pos.x, pos.y, shotst.cpos.x, (shotst.shooter == SHOOTER::PLAYER ? shotst.cpos.y : shotst.cpos.y++), (range / 180.0f));
}

void ShotRadiation::Delete()
{
	lifeFlag = false;
}

ShotRadiation::~ShotRadiation()
{
}

void ShotRadiation::Update()
{
	(this->*updater)();
}

void ShotRadiation::Draw()
{
	CharacterObject::Draw(charaData.img);
}

void ShotRadiation::rotation2D(float * xp, float * yp, float x, float y, float xc, float yc, float theta)
{
	y = -y;
	yc = -yc;
	*xp = (x - xc) * cos(theta) - (y - yc) * sin(theta) + xc;
	*yp = -1.0 * ((x - xc) * sin(theta) + (y - yc) * cos(theta) + yc);
}