#include "ShotNormal.h"
#include "../../Game.h"
#include "../Enemy.h"
#include <DxLib.h>

ShotNormal::ShotNormal(const Player& player/*, const Enemy& enemy*/) : Shot(player/*, enemy*/),player(player), enemy(enemy)
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot1");
	SetCharaSize(0.5f);
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());

	updater = &ShotNormal::Move;
}

ShotNormal::ShotNormal(const ShotNormal & d) : Shot(d.player/*, d.enemy*/),player(player), enemy(enemy)
{
	*this = d;
}

void ShotNormal::operator=(const ShotNormal &d)
{
	memcpy(this, &d, sizeof(ShotNormal));
}

Shot * ShotNormal::Clone()
{
	return new ShotNormal(*this);
}

void ShotNormal::Move()
{
}

ShotNormal::~ShotNormal()
{
}

void ShotNormal::Update()
{
	(this->*updater)();
}

void ShotNormal::Draw()
{
	CharacterObject::Draw(img);
}
