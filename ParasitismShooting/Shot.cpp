#include "Shot.h"
#include <DxLib.h>
#include "Player.h"
#include "Peripheral.h"
#include "GameScreen.h"

Shot::Shot()
{
	DxLib::LoadDivGraph("img/lightbullet.png", 8, 8, 1, 60, 60, img, true);
	for (int j = 0; j < SHOT_MAX; j++)
	{
		cShot[j].flag = 0;
		cShot[j].pos = { 0,0 };
		cShot[j].vel = { 0,0 };
		cShot[j].Dir = { 0,0 };
		cShot[j].level = 0;
		cShot[j].ptn = 0;
	}
	cnt = 0;
	GameScreen gscreen;
	Vector2 screenSize = gscreen.GetGSSize();

	up = 0;
	right = screenSize.x;
	left = 0;
	down = screenSize.y;
}


Shot::~Shot()
{
}

void Shot::Update()
{
	for (int j = 0; j < SHOT_MAX; j++)
	{
		if (cShot[j].flag == 1)
		{
			cShot[j].pos.x += cos(cShot[j].Dir.x) * cShot[j].vel.x;
			cShot[j].pos.y += cos(cShot[j].Dir.y) * cShot[j].vel.y;
		//	Draw();
		}
	}
	OutofScreen();
	
}

void Shot::cSHOT(Vector2 pos)
{
	setBullet(pos, { 0,-30 }, { 0,0 }, 1, 1);
}

void Shot::setBullet(Vector2 pos, Vector2 vel, Vector2 Dir, int level, int ptn)
{
	int k = 0;
	for (int j = 0; j < 2; j++)
	{
		if ( (k = SearchBullet()) != -1)
		{
			cShot[k].flag	 = 1;
			cShot[k].pos	 = pos;
			cShot[k].vel	 = vel;
			cShot[k].Dir	 = Dir;
			cShot[k].level	 = level;
			cShot[k].ptn	 = ptn;
		}
	}
}

void Shot::Draw(void)
{
	for (int j = 0; j < SHOT_MAX; j++)
	{
		if (cShot[j].flag == 1)
		{
			DxLib::DrawExtendGraph(cShot[j].pos.x, cShot[j].pos.y, cShot[j].pos.x + 20, cShot[j].pos.y + 20, img[0], true);
		}
	}
}

int Shot::SearchBullet(void)
{
	for (int j = 0; j < SHOT_MAX; j++)
	{
		if (cShot[j].flag == 0)
		{
			return j;
		}
	}
	return -1;
}

void Shot::OutofScreen(void)
{
	for (int j = 0; j < SHOT_MAX; j++)
	{
		if (cShot[j].flag == 1)
		{
			if (cShot[j].pos.x < left)
			{
				cShot[j].flag = 0;
			}
			else if (cShot[j].pos.x > right)
			{
				cShot[j].flag = 0;
			}
			if (cShot[j].pos.y < up)
			{
				cShot[j].flag = 0;
			}
			else if (cShot[j].pos.y > down)
			{
				cShot[j].flag = 0;
			}
		}
	}
}