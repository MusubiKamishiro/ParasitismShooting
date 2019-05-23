#include "Player.h"
#include <DxLib.h>
#include <algorithm>
#include "../Peripheral.h"
#include "../GameScreen.h"


Player::Player()
{
	ReadActionFile("action/player.act");
	ChangeAction("Idle");
	SetCharaSize(0.1f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());
	charaData.HP = 1;
	charaData.moveVel = 3.0;
	charaData.shotType = "ShotWeak";
	originData = charaData;

	gs.reset(new GameScreen());
	Vector2 gssize = gs->GetGSSize();

	up = gs->outscreen;
	right = gssize.x;
	left = gs->outscreen;
	down = gssize.y;

	vel = Vector2f(0, 0);
	startPos = Vector2f(gssize.x / 2 + gs->outscreen / 2, gssize.y - 20);
	pos = startPos;
	icount = ccount = 0;
	parasFlag = false;
	pinchFlag = false;

	updater = &Player::Move;

	efect = DxLib::LoadGraph("img/tnm.png");
}

Player::Player(const CharaData& cdata)
{
	ReadActionFile("action/player.act");
	ChangeAction("Idle");
	SetCharaSize(0.1f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());
	charaData.HP = 1;
	charaData.moveVel = 3.0;
	charaData.shotType = "ShotWeak";
	originData = charaData;

	// 前のステージでの最後の姿を持ってくる
	charaData = cdata;

	gs.reset(new GameScreen());
	Vector2 gssize = gs->GetGSSize();

	up = gs->outscreen;
	right = gssize.x;
	left = gs->outscreen;
	down = gssize.y;

	vel = Vector2f(0, 0);
	startPos = Vector2f(gssize.x / 2 + gs->outscreen / 2, gssize.y - 20);
	pos = startPos;
	icount = ccount = 0;
	charaData.shotType == "ShotWeak" ? parasFlag = false : parasFlag = true;
	pinchFlag = false;

	updater = &Player::Move;

	efect = DxLib::LoadGraph("img/tnm.png");
}

Player::~Player()
{
}

void Player::Update(const Peripheral &p)
{
	if (p.IsPressing(key.GetNowKey(CANCEL)))
	{
		++ccount;
		if (ccount > 120)
		{
			if (parasFlag)
			{
				updater = &Player::ParasiticCancel;
			}
			ccount = 0;
		}
	}
	else
	{
		ccount = 0;
	}

	// 移動方向が決まる
	(this->*updater)(p);

	pos += vel;
	NotOutOfRange();
}


void Player::Move(const Peripheral & p)
{
	vel = Vector2f();
	float mvel = charaData.moveVel;

	if (p.IsPressing(key.GetNowKey(SLOW)))
	{
		mvel = charaData.moveVel / 2;
	}

	// ボタンを押したら移動(今回は8方向)
	if (p.IsPressing(key.GetNowKey(UP)))
	{
		vel += Vector2f(0, -mvel);
	}
	if (p.IsPressing(key.GetNowKey(DOWN)))
	{
		vel += Vector2f(0, mvel);
	}
	if (p.IsPressing(key.GetNowKey(RIGHT)))
	{
		vel += Vector2f(mvel, 0);
	}
	if (p.IsPressing(key.GetNowKey(LEFT)))
	{
		vel += Vector2f(-mvel, 0);
	}

	// 斜め移動の際はスピード調整
	if ((vel.x != 0) && (vel.y != 0))
	{
		vel /= 1.4142136;
	}
}

void Player::Damage(const Peripheral & p)
{
	if (updater != &Player::Invincible)
	{
		--charaData.HP;
		if (charaData.HP <= 0)
		{
			if (parasFlag)
			{
				charaData.HP = 1;
				parasFlag = false;
				ParasiticCancel(p);
			}
			else
			{
				updater = &Player::Die;
				Die(p);
			}
		}
		else
		{
			updater = &Player::Invincible;
		}
	}
}

void Player::Invincible(const Peripheral & p)
{
	if (icount >= 180)
	{
		icount = 0;
		updater = &Player::Move;
	}
	else
	{
		++icount;
	}
	Move(p);
}

void Player::Die(const Peripheral &p)
{
	vel = Vector2f(0, 0);
}

void Player::Reborn(const Peripheral & p)
{
	charaData = originData;
	updater = &Player::Invincible;
}


void Player::Parasitic(const Peripheral & p, const CharaData& cdata)
{
	parasFlag = true;

	charaData = cdata;
	charaData.HP = cdata.HP / 3;

	icount = 0;
	updater = &Player::Invincible;
}

void Player::ParasiticCancel(const Peripheral & p)
{
	charaData = originData;
	pinchFlag = true;
	parasFlag = false;
	updater = &Player::Invincible;
}


void Player::Draw(const int& time)
{
	if (updater != &Player::Invincible)
	{
		CharacterObject::Draw(charaData.img);
	}
	else
	{
		if ((time / 5) % 2)
		{
			DxLib::SetDrawBright(0, 255, 0);
			CharacterObject::Draw(charaData.img);
			DxLib::SetDrawBright(255, 255, 255);
		}
		else
		{
			CharacterObject::Draw(charaData.img);
		}
	}

	float a = (time % 30) / 90.f;
	
	float b = (30 - (time % 30)) * 8;
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (b));
	DxLib::SetDrawBright(255, 0, 0);
	DxLib::DrawRotaGraph(pos.x, pos.y, a, 0, efect, true);
	DxLib::SetDrawBright(255, 255, 255);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}


void Player::NotOutOfRange()
{
	// 範囲外にはいかせないぜ
	if (pos.x <= (left + rect.Width() / 2))
	{
		pos.x = (left + rect.Width() / 2);
	}
	else if (pos.x >= (right - rect.Width() / 2))
	{
		pos.x = (right - rect.Width() / 2);
	}

	if (pos.y <= (up + rect.Height() / 2))
	{
		pos.y = (up + rect.Height() / 2);
	}
	else if (pos.y >= (down - rect.Height() / 2))
	{
		pos.y = (down - rect.Height() / 2);
	}
}
