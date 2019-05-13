#include "ShotShotgun.h"
#include "../../Game.h"
#include "../Enemy.h"
#include <DxLib.h>

ShotShotgun::ShotShotgun(const Player& player/*, const Enemy& enemy*/) : Shot(player/*, enemy*/),player(player), enemy(enemy)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot2");
	SetCharaSize(0.5f);
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());

	updater = &ShotShotgun::Move;
}

ShotShotgun::ShotShotgun(const ShotShotgun & d) : Shot(d.player/*, d.enemy*/),player(player), enemy(enemy)
{
	*this = d;
}

void ShotShotgun::operator=(const ShotShotgun &d)
{
	memcpy(this, &d, sizeof(ShotShotgun));
}

Shot * ShotShotgun::Clone()
{
	return new ShotShotgun(*this);
}

void ShotShotgun::Move()
{
	pos.x += cos(angle) * Speed;
	pos.y += sin(angle) * Speed;
}

void ShotShotgun::Delete()
{
	lifeFlag = false;
}

ShotShotgun::~ShotShotgun()
{
}

void ShotShotgun::Update()
{
	(this->*updater)();
}

void ShotShotgun::Draw()
{
	CharacterObject::Draw(img);
}
