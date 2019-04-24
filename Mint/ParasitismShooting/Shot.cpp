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
		cShot[j].pos	 = { 0,0 };
		cShot[j].vel	 = { 0,0 };
		cShot[j].Dir	 = { 0,0 };
		cShot[j].movePtn = 0;
		cShot[j].level	 = 0;
		cShot[j].shotPtn	 = 0;
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
		}
	}
	OutofScreen();
	
}

void Shot::cSHOT(Vector2 pos, int shotPtn)
{
	setBullet(pos, { 1,-10}, { 0,0 },1, 4, shotPtn);
}

void Shot::setBullet(Vector2 pos, Vector2 vel, Vector2 Dir, int movePtn, int level, int shotPtn)
{
	int k = 0;
	for (int j = 0; j < level; j++)
	{
		if ( (k = SearchBullet()) != -1)
		{
			if (shotPtn == SHOT_PTN::WEAK)
			{

			}
			else if (shotPtn == SHOT_PTN::NORMAL)
			{
				cShot[k].flag = 1;
				cShot[k].pos = { pos.x - 10 + NormalPosPtnX[j],pos.y  + NormalPosPtnY[j] };
				cShot[k].vel = vel;
				cShot[k].Dir = Dir;
				cShot[k].movePtn = movePtn;
				cShot[k].level = level;
				cShot[k].shotPtn = shotPtn;
			}
			else if (shotPtn == SHOT_PTN::SHOTGUN)
			{

			}
			else if (shotPtn == SHOT_PTN::TRACKING)
			{

			}
			else if (shotPtn == SHOT_PTN::RADIATION)
			{

			}
			else if (shotPtn == SHOT_PTN::LASER)
			{

			}
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
			if (cShot[j].pos.x < left - 30)
			{
				cShot[j].flag = 0;
			}
			else if (cShot[j].pos.x > right + 30)
			{
				cShot[j].flag = 0;
			}
			if (cShot[j].pos.y < up - 30)
			{
				cShot[j].flag = 0;
			}
			else if (cShot[j].pos.y > down + 30)
			{
				cShot[j].flag = 0;
			}
		}
	}
}