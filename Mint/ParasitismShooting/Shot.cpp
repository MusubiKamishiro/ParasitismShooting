#include "Shot.h"
#include <DxLib.h>
#include <iostream>
#include <random>
#include "Character/Player.h"
#include "Peripheral.h"
#include "GameScreen.h"
#define Fixed  double
#define Radian double
struct Node
{
	double x, y;
	double speed;
	double angle;
};

static const int NODE_NUM = 8;
static const int LINK_NUM = 16;
static struct Node node[NODE_NUM][LINK_NUM];

static int target_x, target_y;

static int graph_laser[2]; // レーザーテクスチャ画像のハンドル

Shot::Shot()
{
	DxLib::LoadDivGraph("img/lightbullet.png", 8, 8, 1, 60, 60, img, true);
	
	cnt = 0;
	GameScreen gscreen;
	Vector2 screenSize = gscreen.GetGSSize();

	up = 0;
	right = screenSize.x;
	left = 0;
	down = screenSize.y;


	a = right / 4;
	b = down / 4;
	c = right / 4 + 30;
	d = down / 4 + 30;

	LoadDivGraph("img/laser.png", 2, 2, 1, 16, 16, graph_laser);
}


Shot::~Shot()
{
}

void Shot::Update()
{
	for (int j = 0; j < cShot.size(); j++)
	{
		if (cShot[j].flag == 1)
		{
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
		}
	}
	OutofScreen();
}


void Shot::setBullet(Vector2f pos, float angle, int Speed, int movePtn, int level, int shotPtn)
{
	for (int j = 0; j < level; j++)
	{
		if (shotPtn == SHOT_PTN::WEAK)
		{
			cShot.push_back({ 1, pos,angle,Speed,movePtn,level,shotPtn });
			cnt++;
		}
		else if (shotPtn == SHOT_PTN::NORMAL)
		{
			cShot.push_back({ 1, pos,angle,Speed,movePtn,level,shotPtn });
			cShot[cnt].flag = 1;
			cShot[cnt].pos = { pos.x - 10 + NormalPosPtnX[j],pos.y + NormalPosPtnY[j] };
			cShot[cnt].angle = -M_PI_2;
			cShot[cnt].Speed = Speed;
			cShot[cnt].movePtn = movePtn;
			cShot[cnt].level = level;
			cShot[cnt].shotPtn = shotPtn;
			cnt++;
		}
		else if (shotPtn == SHOT_PTN::SHOTGUN)
		{
			cShot.push_back({ 1, pos,angle,Speed,movePtn,level,shotPtn });
			cShot[cnt].flag = 1;
			cShot[cnt].pos = pos;
			cShot[cnt].angle = -(((angle + (M_PI / level))  * j) + M_PI / 6);
			cShot[cnt].Speed = Speed;
			cShot[cnt].movePtn = movePtn;
			cShot[cnt].level = level;
			cShot[cnt].shotPtn = shotPtn;
			cnt++;
		}
		else if (shotPtn == SHOT_PTN::TRACKING)
		{
			cShot.push_back({ 1, pos,angle,Speed,movePtn,level,shotPtn });
			cShot[cnt].flag = 1;
			cShot[cnt].pos = { pos.x + 20 * j,pos.y };
			cShot[cnt].angle = ShotAngle(pos);
			cShot[cnt].Speed = Speed;
			cShot[cnt].movePtn = movePtn;
			cShot[cnt].level = level;
			cShot[cnt].shotPtn = shotPtn;
			cnt++;
		}
		else if (shotPtn == SHOT_PTN::RADIATION)
		{
			cShot.push_back({ 1, pos,angle,Speed,movePtn,level,shotPtn });
			cShot[cnt].flag = 1;
			cShot[cnt].pos = pos;
			cShot[cnt].angle = -(angle + M_PI_2 / (level / 4)  * j);
			cShot[cnt].Speed = Speed;
			cShot[cnt].movePtn = movePtn;
			cShot[cnt].level = level;
			cShot[cnt].shotPtn = shotPtn;
			cnt++;
		}
		else if (shotPtn == SHOT_PTN::RANDOM)
		{
			std::random_device rd;

			std::mt19937 mt(rd());

			std::uniform_int_distribution<int> rand(1, 10);
			cShot.push_back({ 1, pos,angle,Speed,movePtn,level,shotPtn });
			cShot[cnt].flag = 1;
			cShot[cnt].pos = { pos.x - (float)(rand(mt) * M_PI * 2) + 10,pos.y - 30 };
			cShot[cnt].angle = ShotAngle(pos);
			cShot[cnt].Speed = Speed;
			cShot[cnt].movePtn = movePtn;
			cShot[cnt].level = level;
			cShot[cnt].shotPtn = shotPtn;
			cnt++;
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
		if (cShot[j].flag == 1)
		{
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
	}
	DrawBox(a, b, c, d, 0xffffff, true);
}


void Shot::OutofScreen(void)
{
	for (int j = 0; j < cShot.size(); j++)
	{
		if (cShot[j].flag == 1)
		{
			if (cShot[j].pos.x < left - 30 || cShot[j].pos.x > right + 30 || cShot[j].pos.y < up - 30 || cShot[j].pos.y > down + 30)
			{
				cShot.erase(cShot.begin() + j);
				cnt--;
			}
		}
	}
}

double Shot::ShotAngle(Vector2f pos)
{
	//Vector2f pPos = player->GetPos();
	//return atan2(pPos.y - pos.y,pPos.x - pos.x);
	return atan2(b - pos.y, a - pos.x);
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
		cShot[n].Speed = 2;
	
		cShot[n].Speed -= 1.2 / 240;
		cShot[n].angle += (M_PI / 10) / 120;
	cShot[n].pos.x += cos(cShot[n].angle) * cShot[n].Speed;
	cShot[n].pos.y += sin(cShot[n].angle) * cShot[n].Speed;

}

void Shot::RandomUpdate(int n)
{
	
	cShot[n].pos.x += cos(cShot[n].angle) * cShot[n].Speed;
	cShot[n].pos.y += sin(cShot[n].angle) * cShot[n].Speed;
}

void Shot::LaserUpdate(int n)
{
}

