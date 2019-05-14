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
	// ‚«‚ê‚¢‚È‚â[‚Âi30”­j
	angle += (M_PI / 10) / 120;
	pos.x += cos(angle) * Speed;
	pos.y += sin(angle) * Speed;
	rotation2D(&pos.x, &pos.y, pos.x, pos.y, cneterPos.x, cneterPos.y, (5.0f / 180.0f));

	//cShot[n].angle += (M_PI / 10) / 120;
	//cShot[n].pos.x += cos(cShot[n].angle) * cShot[n].Speed;
	//cShot[n].pos.y += sin(cShot[n].angle) * cShot[n].Speed;
	//rotation2D(&cShot[n].pos.x, &cShot[n].pos.y, cShot[n].pos.x, cShot[n].pos.y, cShot[n].cneterPos.x, cShot[n].cneterPos.y, (5.0f / 180.0f));
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
	CharacterObject::Draw(img);
}

void ShotRadiation::rotation2D(float * xp, float * yp, float x, float y, float xc, float yc, float theta)
{
	y = -y;
	yc = -yc;
	*xp = (x - xc) * cos(theta) - (y - yc) * sin(theta) + xc;
	*yp = -1.0 * ((x - xc) * sin(theta) + (y - yc) * cos(theta) + yc);
}