#include "Ika.h"
#include "../Game.h"
#include <DxLib.h>
#include "EnemyActionPattern.h"

const float DELTA = 0.001;


Ika::Ika(const Player& player) : Enemy(player), player(player)
{
	ReadActionFile("action/squid.act");
	ChangeAction("Idle");
	SetCharaSize(0.8f);
	charaData.shotReady = false;
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());
	score = 20000;

	actFlag = true;
	eAction.reset(new EnemyActionPattern());

	updater = &Ika::Move;

	actFlag = true;
	bossFlag = false;
	nextStageFlag = false;
	basePos = { 310,120 };
}

Ika::Ika(const Ika& d) : Enemy(d.player), player(player)
{
	*this = d;
}

void Ika::operator=(const Ika& d)
{
	memcpy(this, &d, sizeof(Ika));
}

Enemy * Ika::Clone()
{
	return new Ika(*this);
}

void Ika::Move()
{
	if (!bossFlag)
	{
		bossFlag = true;
	}

	if (charaData.shotReady == true || actFlag == false)
	{
		charaData.shotReady = false;
	}
	orginalMove(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.shotReady);
	if (actFlag)
	{
		cnt++;
	}
}

void Ika::Die()
{
	scoreFlag = true;
	actFlag = false;
	lifeFlag = false;
	bossFlag = false;
	nextStageFlag = true;
}

void Ika::Stunning()
{
	if (charaData.shotReady)
	{
		charaData.shotReady = false;
	}
	eAction->Update(movePtn, pos, charaData.moveVel, cnt, wait, shotCnt, charaData.SP, charaData.shotReady);
}

void Ika::StunDamage()
{
	if (actFlag)
	{
		--charaData.SP;
	}
	if (charaData.SP == 100)
	{
		cnt = 0;
		actFlag = false;
	}
	if (charaData.SP <= 0)
	{
		actFlag = false;
		charaData.shotType = "Shotgun";
		charaData.shotLevel = 5;
		updater = &Ika::Stunning;
	}
}

Ika::~Ika()
{
}

void Ika::Update()
{
	(this->*updater)();
}

void Ika::Draw(int time)
{
	if (updater != &Ika::Stunning)
	{
		CharacterObject::Draw(charaData.img);
	}
	else
	{
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs((time * 5 % 255) - 127) + 128);
		CharacterObject::Draw(charaData.img);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Ika::Damage()
{
	if (actFlag)
	{
		charaData.HP -= 1;
	}
	if (charaData.HP == 300)
	{
		if (pos != basePos)
		{
			vecAngle = atan2(basePos.y - pos.y, basePos.x - pos.x);
			actFlag = false;
			if (charaData.shotReady == true)
			{
				charaData.shotReady = false;
			}
		}
		cnt = 0;
		charaData.SP = 100;
	}
	if (charaData.HP <= 0)
	{
		updater = &Ika::Die;
	}
}

void Ika::orginalMove(int movePtn, Vector2f & pos, float speed, int cnt, int wait, int shotCnt, int charSP, bool & ShotReady)
{
	if (!actFlag)
	{
		pos.x += cos(vecAngle) * speed / 4;
		pos.y += sin(vecAngle) * speed / 4;
		if (basePos.x - pos.x < DELTA)
		{
			if (basePos.y - pos.x < DELTA)
			{
				actFlag = true;
			}
		}
	}
	if (cnt < 1800 && charaData.HP >300 && charaData.SP > 100 && actFlag == true)
	{
		switch (cnt)
		{
		case 0:
			charaData.shotType = "Shotgun";
			charaData.shotLevel = 7;
			break;
		case 30:
			charaData.shotReady = true;
			break;
		case 45:
			charaData.shotReady = true;
			break;
		case 60:
			charaData.shotReady = true;
			break;
		case 65:
			charaData.shotType = "Tracking";
			charaData.shotLevel = 3;
			break;
		case 120:
			charaData.shotReady = true;
			break;
		case 150:
			charaData.shotReady = true;
			break;
		case 155:
			charaData.shotType = "CircleCross";
			charaData.shotLevel = 30;
			break;
		case 260:
			charaData.shotReady = true;
			break;
		case 265:
			charaData.shotType = "Shotgun";
			charaData.shotLevel = 11;
			break;
		case 280:
			charaData.shotReady = true;
			break;
		case 285:
			charaData.shotType = "CircleCross";
			charaData.shotLevel = 30;
			break;
		case 360:
			charaData.shotReady = true;
			break;
		case 365:
			charaData.shotType = "Normal";
			charaData.shotLevel = 2;
			break;
		case 420:
			charaData.shotReady = true;
			break;
		case 440:
			charaData.shotReady = true;
			break;
		case 460:
			charaData.shotReady = true;
			break;
		case 480:
			charaData.shotReady = true;
			break;
		case 500:
			charaData.shotReady = true;
			break;
		case 520:
			charaData.shotReady = true;
			break;
		case 540:
			charaData.shotReady = true;
			break;
		case 545:
			charaData.shotType = "Radiation";
			charaData.shotLevel = 30;
			break;
		case 650:
			charaData.shotReady = true;
			break;
		case 670:
			charaData.shotReady = true;
			break;
		case 690:
			charaData.shotReady = true;
			break;
		case 710:
			charaData.shotReady = true;
			break;
		case 730:
			charaData.shotReady = true;
			break;
		case 725:
			charaData.shotType = "Shotgun";
			charaData.shotLevel = 9;
			break;
		case 800:
			charaData.shotReady = true;
			break;
		case 820:
			charaData.shotReady = true;
			break;
		case 840:
			charaData.shotReady = true;
			break;
		case 860:
			charaData.shotReady = true;
			break;
		case 880:
			charaData.shotReady = true;
			break;
		case 900:
			charaData.shotReady = true;
			break;
		case 905:
			charaData.shotType = "Tracking";
			charaData.shotLevel = 3;
			break;
		case 950:
			charaData.shotReady = true;
			break;
		case 1000:
			charaData.shotReady = true;
			break;
		case 1050:
			charaData.shotReady = true;
			break;
		case 1055:
			charaData.shotType = "Shotgun";
			charaData.shotLevel = 36;
			break;
		case 1100:
			charaData.shotReady = true;
			break;
		case 1120:
			charaData.shotReady = true;
			break;
		case 1140:
			charaData.shotReady = true;
			break;
		case 1260:
			charaData.shotReady = true;
			break;
		case 1280:
			charaData.shotReady = true;
			break;
		case 1320:
			charaData.shotReady = true;
			break;
		case 1340:
			charaData.shotReady = true;
			break;
		case 1360:
			charaData.shotReady = true;
			break;
		case 1400:
			charaData.shotReady = true;
			break;
		case 1395:
			charaData.shotType = "CircleCross";
			charaData.shotLevel = 30;
			break;
		case 1450:
			charaData.shotReady = true;
			break;
		case 1455:
			charaData.shotType = "Normal";
			charaData.shotLevel = 5;
			break;
		case 1480:
			charaData.shotReady = true;
			break;
		case 1500:
			charaData.shotReady = true;
			break;
		case 1520:
			charaData.shotReady = true;
			break;
		case 1525:
			charaData.shotType = "CircleCross";
			charaData.shotLevel = 30;
			break;
		case 1600:
			charaData.shotReady = true;
			break;
		case 1605:
			charaData.shotType = "Normal";
			charaData.shotLevel = 3;
			break;
		case 1630:
			charaData.shotReady = true;
			break;
		case 1650:
			charaData.shotReady = true;
			break;
		case 1670:
			charaData.shotReady = true;
			break;
		case 1675:
			charaData.shotType = "Shotgun";
			charaData.shotLevel = 36;
			break;
		case 1700:
			charaData.shotReady = true;
			break;
		case 1720:
			charaData.shotReady = true;
			break;
		default:
			break;
		}
	}

	else if (charaData.HP < 301 || charaData.SP < 101 && actFlag == true)
	{
		switch (cnt)
		{

		case 1:
			if (stageNum == 1)
			{
				charaData.shotType = "Shotgun";
			}
			else
			{
				charaData.shotType = "Radiation";
			}
			break;
		case 5:
		case 125:
		case 245:
		case 365:
		case 495:
		case 615:
		case 725:
			(charaData.shotType == "Shotgun" ? charaData.shotLevel = 7 : charaData.shotLevel = 25);
			break;
		case 65:
		case 185:
		case 305:
		case 435:
		case 555:
		case 675:
		case 795:
			(charaData.shotType == "Shotgun" ? charaData.shotLevel = 15 : charaData.shotLevel = 35);
			break;
		default:
			if (cnt % 10 == 0)
			{
				if (cnt % 15 == 0)
				{
					charaData.shotReady = true;
					break;
				}
			}
		}
	}

	else
	{
		if (charaData.HP > 300)
		{
			for (int j = 0; j < charaData.HP - 300; j++)
			{
				Damage();
			}
		}
	}
	if ((charaData.HP > 300) && (charaData.SP > 100))
	{
		if (cnt < 30)
		{
			pos.x += speed;
		}
		else if (cnt < 90)
		{
			pos.x -= speed;
		}
		else if (cnt > 120 && cnt < 150)
		{
			pos.y += speed / 4;
		}
		else if (cnt > 180 && cnt < 210)
		{
			pos.x += speed;
			pos.y -= speed / 4;
		}
		else if (cnt > 240 && cnt < 270)
		{
			pos.x += speed;
		}
		else if (cnt > 420 && cnt < 540)
		{
			pos.x -= speed / 4;
		}
		else if (cnt > 800 && cnt < 920)
		{
			pos.x -= speed / 4;
		}
		else if (cnt > 1100 && cnt < 1400)
		{
			pos.x += speed / 10;
		}
	}
}
