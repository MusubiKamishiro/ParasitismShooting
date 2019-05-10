#include "Shot.h"
#include <DxLib.h>
#include <random>
#include "Character/Player.h"
#include "Peripheral.h"
#include "GameScreen.h"

Shot::Shot()
{
	ReadActionFile("action/shot.act");
	ChangeAction("Shot1");
	SetCharaSize(0.5f);
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());
	
	GameScreen gscreen;
	Vector2 screenSize = gscreen.GetGSSize();

	up = 0;
	right = screenSize.x + gscreen.outscreen;
	left = 0;
	down = screenSize.y + gscreen.outscreen;

	interval = 0;
}


Shot::~Shot()
{
}

void Shot::Update()
{
	for (int j = 0; j < cShot.size(); j++)
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
	OutofScreen();
	
}


void Shot::setBullet(Vector2f pos, float angle, int Speed, int movePtn, int level, int shotPtn,int shoter)
{
	for (int j = 0; j < level; j++)
	{
		if (shotPtn == SHOT_PTN::WEAK)
		{
			cShot.push_back({ pos, angle, Speed, movePtn, level, shotPtn, shoter, "Shot1" });
		}
		else if (shotPtn == SHOT_PTN::NORMAL)
		{
			cShot.push_back({ { pos.x - 10 + NormalPosPtnX[j],pos.y + NormalPosPtnY[j] }, -M_PI_2, Speed, movePtn, level, shotPtn, shoter, "Shot1" });
		}
		else if (shotPtn == SHOT_PTN::SHOTGUN)
		{
			cShot.push_back({ pos, -(((angle + (M_PI / level))  * j) + M_PI / 6), Speed, movePtn, level, shotPtn, shoter, "Shot2" });
		}
		else if (shotPtn == SHOT_PTN::TRACKING)
		{
			cShot.push_back({ { pos.x + 20 * j,pos.y },ShotAngle(pos), Speed, movePtn, level, shotPtn, shoter, "Shot3" });
		}
		else if (shotPtn == SHOT_PTN::RADIATION)
		{
			cShot.push_back({ pos, -(angle + M_PI_2 / (level / 4)  * j), Speed, movePtn, level, shotPtn, shoter, "Shot4" });
		}
		else if (shotPtn == SHOT_PTN::RANDOM)
		{
			std::random_device rd;
			std::mt19937 mt(rd());

			std::uniform_int_distribution<int> rand(1, 10);
			cShot.push_back({ { pos.x - (float)(rand(mt) * M_PI * 2) + 10,pos.y - 30 }, ShotAngle(pos), Speed, movePtn, level, shotPtn, shoter, "Shot5" });
		}
		else if (shotPtn == SHOT_PTN::LASER)
		{
			cShot.push_back({ pos, angle, Speed, movePtn, level, shotPtn, shoter, "Shot1" });
		}
	}
}

void Shot::ShotBullet(const Peripheral & p, const Vector2f& pos)
{
	if (interval % 3 == 0)
	{
		if (p.IsPressing(PAD_INPUT_2))
		{
			setBullet(pos, 0, 5, 0, 4, SHOT_PTN::NORMAL, SHOTER::PLAYER);
		}
		if (p.IsPressing(PAD_INPUT_4))
		{
			setBullet(pos, 0, 5, 0, 3, SHOT_PTN::SHOTGUN, SHOTER::PLAYER);
		}
		if (p.IsPressing(PAD_INPUT_5))
		{
			setBullet(pos, 0, 5, 0, 1, SHOT_PTN::TRACKING, SHOTER::PLAYER);
		}
		if (p.IsPressing(PAD_INPUT_6))
		{
			setBullet(pos, 0, 5, 0, 50, SHOT_PTN::RADIATION, SHOTER::PLAYER);
		}
		if (p.IsPressing(PAD_INPUT_10))
		{
			setBullet(pos, 0, 5, 0, 100, SHOT_PTN::RANDOM, SHOTER::PLAYER);
		}
	}
	interval++;
}

void Shot::Draw(void)
{
	for (int j = 0; j < cShot.size(); j++)
	{
		pos = cShot[j].pos;
		nowActionName = cShot[j].shotname;

		CharacterObject::Draw(img);
	}
}


void Shot::OutofScreen(void)
{
	for (int j = 0; j < cShot.size(); j++)
	{
		if (cShot[j].pos.x < left - rect.Width()/2 || cShot[j].pos.x > right + rect.Width()/2 || cShot[j].pos.y < up - rect.Height()/2 || cShot[j].pos.y > down + rect.Height()/2)
		{
			cShot.erase(cShot.begin() + j);
			j--;
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

void Shot::rotation2D(float * xp, float * yp, float x, float y, float xc, float yc, float theta)
{
	y = -y;
	yc = -yc;
	*xp = (x - xc) * cos(theta) - (y - yc) * sin(theta) + xc;
	*yp = -1.0 * ((x - xc) * sin(theta) + (y - yc) * cos(theta) + yc);
}


