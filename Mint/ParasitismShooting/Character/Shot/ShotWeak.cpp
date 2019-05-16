#include "ShotWeak.h"
#include "../../Game.h"
#include "../Enemy.h"
#include <DxLib.h>

ShotWeak::ShotWeak(const Player& player/*, const Enemy& enemy*/) : Shot(player/*, enemy*/), player(player), enemy(enemy)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot1");
	SetCharaSize(0.5f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());

	updater = &ShotWeak::Move;
}

ShotWeak::ShotWeak(const ShotWeak & d) : Shot(d.player/*, d.enemy*/), player(player), enemy(enemy)
{
	*this = d;
}

void ShotWeak::operator=(const ShotWeak &d)
{
	memcpy(this, &d, sizeof(ShotWeak));
}

Shot * ShotWeak::Clone()
{
	return new ShotWeak(*this);
}

void ShotWeak::Move()
{
	pos.x += cos(shotst.angle) * shotst.speed;
	pos.y += sin(shotst.angle) * shotst.speed;
}

void ShotWeak::Delete()
{
	lifeFlag = false;
}

ShotWeak::~ShotWeak()
{
}

void ShotWeak::Update()
{
	(this->*updater)();
}

void ShotWeak::Draw()
{
	CharacterObject::Draw(charaData.img);
}
