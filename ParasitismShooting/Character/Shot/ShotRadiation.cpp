#include "ShotRadiation.h"
#include "../../Game.h"
#include "../Enemy.h"
#include <DxLib.h>

ShotRadiation::ShotRadiation(const Player& player/*, const Enemy& enemy*/) : Shot(player/*, enemy*/),player(player), enemy(enemy)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot4");
	SetCharaSize(0.5f);
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());

	updater = &ShotRadiation::Move;
}

ShotRadiation::ShotRadiation(const ShotRadiation & d) : Shot(d.player/*, d.enemy*/),player(player), enemy(enemy)
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
	CharacterObject::Draw(img);
}
