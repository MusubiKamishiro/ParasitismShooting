#include "ShotNormal.h"
#include "../../Game.h"
#include <DxLib.h>

ShotNormal::ShotNormal(const Shot & shot) : Shot(shot),shot(shot)
{
	updater = &ShotNormal::Move;
}

ShotNormal::ShotNormal(const ShotNormal & d) : Shot(d.shot),shot(shot)
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
}
