#include "Shot.h"
#include <DxLib.h>
#include "Player.h"
#include "Peripheral.h"

Shot::Shot()
{
	DxLib::LoadDivGraph("img/lightbullet.png", 8, 8, 1, 60, 60, img, true);
	for (int j = 0; j < SHOT_MAX; j++)
	{
		cShot[j].flag = false;
		cShot[j].pos = { 0,0 };
		cShot[j].vel = { 0,0 };
		cShot[j].Dir = { 0,0 };
		cShot[j].level = 0;
		cShot[j].ptn = 0;
	}
}


Shot::~Shot()
{
}

void Shot::Update()
{
	for (int j = 0; j < SHOT_MAX; j++)
	{
		if (cShot[j].flag == true)
		{
			cShot[j].pos.x += cos(cShot[j].Dir.x) * cShot[j].vel.x;
			cShot[j].pos.y += cos(cShot[j].Dir.y) * cShot[j].vel.y;
			Draw();
		}
	}
	
}

void Shot::cSHOT(Vector2 pos)
{
}

void Shot::setBullet(Vector2 pos, Vector2 vel, Vector2 Dir, int level, int ptn)
{
	for (int j = 0; j < SHOT_MAX; j++)
	{
		if ((SearchBullet()) != false)
		{
			cShot[j].flag	 = true;
			cShot[j].pos	 = pos;
			cShot[j].vel	 = vel;
			cShot[j].Dir	 = Dir;
			cShot[j].level	 = level;
			cShot[j].ptn	 = ptn;
		}
	}
}

void Shot::Draw(void)
{
	for (int j = 0; j < SHOT_MAX; j++)
	{
		DxLib::DrawExtendGraph(cShot[j].pos.x, cShot[j].pos.y, cShot[j].pos.x + 20, cShot[j].pos.y + 20, img[0], true);

	}
}

bool Shot::SearchBullet(void)
{
	for (int j = 0; j < SHOT_MAX; j++)
	{
		if (cShot[j].flag == false)
		{
			return true;
		}
	}
	return false;
}
