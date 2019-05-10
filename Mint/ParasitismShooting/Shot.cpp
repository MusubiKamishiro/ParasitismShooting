#include "Shot.h"
#include <DxLib.h>
#include <iostream>
#include <random>
#include "Character/Player.h"
#include "Peripheral.h"
#include "GameScreen.h"

Shot::Shot()
{
	DxLib::LoadDivGraph("img/lightbullet.png", 8, 8, 1, 60, 60, img, true);
	
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
	for (int j = 0; j < cShot.size(); j++)
	{
		/*if (cShot[j].flag == 1)
		{*/
			if (cShot[j].shotPtn == SHOT_PTN::NORMAL)
			{
				NormalUpdate(j);
			}
			if (cShot[j].shotPtn == SHOT_PTN::SHOTGUN)
			{
				ShotgunUpdate(j);
			}
			if (cShot[j].shotPtn == SHOT_PTN::TRACKING)
			{
				TrackingUpdate(j);
			}
			if (cShot[j].shotPtn == SHOT_PTN::RADIATION)
			{
				RadiationUpdate(j);
			}
			if (cShot[j].shotPtn == SHOT_PTN::RANDOM)
			{
				RandomUpdate(j);
			}
			if (cShot[j].shotPtn == SHOT_PTN::LASER)
			{
				LaserUpdate(j);
			}
	//	}
	}
	OutofScreen();
	
}


void Shot::setBullet(Vector2f pos, float angle, int Speed, int movePtn, int level, int shotPtn,int shoter)
{
	for (int j = 0; j < level; j++)
	{
		if (shotPtn == SHOT_PTN::WEAK)
		{
			cShot.push_back({ 1, pos,angle,Speed,movePtn,level,shotPtn ,shoter });
			cnt++;
		}
		else if (shotPtn == SHOT_PTN::NORMAL)
		{
			cShot.push_back({ 1, { pos.x - 10 + NormalPosPtnX[j],pos.y + NormalPosPtnY[j] },-M_PI_2,Speed,movePtn,level,shotPtn,shoter });
		}
		else if (shotPtn == SHOT_PTN::SHOTGUN)
		{
			cShot.push_back({ 1, pos,-(((angle + (M_PI / level))  * j) + M_PI / 6),Speed,movePtn,level,shotPtn,shoter });
		}
		else if (shotPtn == SHOT_PTN::TRACKING)
		{
			cShot.push_back({ 1, { pos.x + 20 * j,pos.y },ShotAngle(pos),Speed,movePtn,level,shotPtn ,shoter });
		}
		else if (shotPtn == SHOT_PTN::RADIATION)
		{
			cShot.push_back({ 1, pos,-(angle + M_PI_2 / (level / 4)  * j),Speed ,movePtn,level,shotPtn ,shoter });
		}
		else if (shotPtn == SHOT_PTN::RANDOM)
		{
			std::random_device rd;

			std::mt19937 mt(rd());

			std::uniform_int_distribution<int> rand(1, 10);
			cShot.push_back({ 1, { pos.x - (float)(rand(mt) * M_PI * 2) + 10,pos.y - 30 },ShotAngle(pos),Speed,movePtn,level,shotPtn });
		}
		else if (shotPtn == SHOT_PTN::LASER)
		{
			cShot.push_back({ 1, pos,angle,Speed,movePtn,level,shotPtn });

			cnt++;
		}
	}
}

void Shot::Draw(void)
{
	for (int j = 0; j < cShot.size(); j++)
	{
		/*if (cShot[j].flag == 1)
		{*/
			if (cShot[j].shotPtn == SHOT_PTN::NORMAL)
			{
				DxLib::DrawExtendGraph(cShot[j].pos.x, cShot[j].pos.y, cShot[j].pos.x + 20, cShot[j].pos.y + 20, img[2], true);
			}
			if (cShot[j].shotPtn == SHOT_PTN::SHOTGUN)
			{
				DxLib::DrawExtendGraph(cShot[j].pos.x, cShot[j].pos.y, cShot[j].pos.x + 20, cShot[j].pos.y + 20, img[4], true);
			}
			if (cShot[j].shotPtn == SHOT_PTN::TRACKING)
			{
				DxLib::DrawExtendGraph(cShot[j].pos.x, cShot[j].pos.y, cShot[j].pos.x + 20, cShot[j].pos.y + 20, img[5], true);
			}
			if (cShot[j].shotPtn == SHOT_PTN::RADIATION)
			{
				DxLib::DrawExtendGraph(cShot[j].pos.x, cShot[j].pos.y, cShot[j].pos.x + 20, cShot[j].pos.y + 20, img[6], true);
			}
			if (cShot[j].shotPtn == SHOT_PTN::RANDOM)
			{
				DxLib::DrawExtendGraph(cShot[j].pos.x, cShot[j].pos.y, cShot[j].pos.x + 20, cShot[j].pos.y + 20, img[1], true);
			}
			if (cShot[j].shotPtn == SHOT_PTN::LASER)
			{

			}
		}
	//}
}


void Shot::OutofScreen(void)
{
	for (int j = 0; j < cShot.size(); j++)
	{
		if (cShot[j].pos.x < left - 30 || cShot[j].pos.x > right + 30 || cShot[j].pos.y < up - 30 || cShot[j].pos.y > down + 30)
		{
			cShot.erase(cShot.begin() + j);
		}
	}
}

double Shot::ShotAngle(Vector2f pos)
{
	//Vector2f pPos = player->GetPos();
	//return atan2(pPos.y - pos.y,pPos.x - pos.x);
	return 0;
}

void Shot::NormalUpdate(int n)
{
	cShot[n].pos.x += cos(cShot[n].angle) * cShot[n].Speed;
	cShot[n].pos.y += sin(cShot[n].angle) * cShot[n].Speed;
}

void Shot::ShotgunUpdate(int n)
{
	cShot[n].pos.x += cos(cShot[n].angle) * cShot[n].Speed;
	cShot[n].pos.y += sin(cShot[n].angle) * cShot[n].Speed;
}

void Shot::TrackingUpdate(int n)
{
	cShot[n].pos.x += cos(cShot[n].angle) * cShot[n].Speed;
	cShot[n].pos.y += sin(cShot[n].angle) * cShot[n].Speed;
}

void Shot::RadiationUpdate(int n)
{
	cShot[n].Speed -= 1.2;
	cShot[n].pos.x += cos(cShot[n].angle) * cShot[n].Speed;
	cShot[n].pos.y += sin(cShot[n].angle) * cShot[n].Speed;
	rotation2D(&cShot[n].pos.x, &cShot[n].pos.y, cShot[n].pos.x, cShot[n].pos.y, 300, 300, (5.0f / 180.0f) * M_PI);

}

void Shot::RandomUpdate(int n)
{
	cShot[n].pos.x += cos(cShot[n].angle) * cShot[n].Speed;
	cShot[n].pos.y += sin(cShot[n].angle) * cShot[n].Speed;
}

void Shot::LaserUpdate(int n)
{
}

void Shot::rotation2D(float * xp, float * yp, float x, float y, float xc, float yc, float theta)
{
	y = -y;
	yc = -yc;
	*xp = (x - xc) * cos(theta) - (y - yc) * sin(theta) + xc;
	*yp = -1.0 * ((x - xc) * sin(theta) + (y - yc) * cos(theta) + yc);
}

