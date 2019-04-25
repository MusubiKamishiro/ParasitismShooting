#include "Shot.h"
#include <DxLib.h>
#include "Character/Player.h"
#include "Peripheral.h"
#include "GameScreen.h"

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
			cShot[j].pos.x += cos(cShot[j].angle) * cShot[j].Speed;
			cShot[j].pos.y += sin(cShot[j].angle) * cShot[j].Speed;
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
			cShot[cnt].angle = -M_PI / 2;
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
			cShot[cnt].angle = -ShotGunAngle[j];
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
			cShot.push_back({ 1, pos,angle,Speed,movePtn,level,shotPtn });
			cShot[cnt].flag = 1;
			cShot[cnt].pos = pos;
			cShot[cnt].angle = ShotAngle(pos) + (rand() * M_PI_4);
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
				DxLib::DrawExtendGraph(cShot[j].pos.x, cShot[j].pos.y, cShot[j].pos.x + 20, cShot[j].pos.y + 20, img[4], true);
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
