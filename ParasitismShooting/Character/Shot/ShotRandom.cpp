#include "ShotRandom.h"
#include "../../Game.h"
#include "../Enemy.h"
#include <DxLib.h>

ShotRandom::ShotRandom(const Player& player/*, const Enemy& enemy*/) : Shot(player/*, enemy*/),player(player), enemy(enemy)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot5");
	SetCharaSize(0.5f);
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());

	updater = &ShotRandom::Move;
}

ShotRandom::ShotRandom(const ShotRandom & d) : Shot(d.player/*, d.enemy*/),player(player), enemy(enemy)
{
	*this = d;
}

void ShotRandom::operator=(const ShotRandom &d)
{
	memcpy(this, &d, sizeof(ShotRandom));
}

Shot * ShotRandom::Clone()
{
	return new ShotRandom(*this);
}

void ShotRandom::Move()
{
	pos.x += cos(angle) * Speed;
	pos.y += sin(angle) * Speed;
}

ShotRandom::~ShotRandom()
{
}

void ShotRandom::Update()
{
	(this->*updater)();
}

void ShotRandom::Draw()
{
	CharacterObject::Draw(img);
}
