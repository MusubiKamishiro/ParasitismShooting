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
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());

	gs.reset(new GameScreen());
	Vector2 gssize = gs->GetGSSize();

	up = gs->outscreen;
	right = gssize.x;
	left = gs->outscreen;
	down = gssize.y;

	vel = Vector2f(0, 0);
	moveVel = 3.0;
	startPos = Vector2f(gssize.x / 2, gssize.y - 20);
	pos = startPos;
	HP = 1;
	count = 0;
	
	updater = &Player::Move;
}

Player::~Player()
{
}

void Player::Update(const Peripheral &p)
{
	// 移動方向が決まる
	(this->*updater)(p);

	pos += vel;
	NotOutOfRange();
}


void Player::Move(const Peripheral & p)
{
	vel = Vector2f();
	float mvel = moveVel;

	if (p.IsPressing(PAD_INPUT_1))
	{
		mvel = moveVel / 2;
	}

	// ボタンを押したら移動(今回は8方向)
	if (p.IsPressing(PAD_INPUT_UP))
	{
		vel += Vector2f(0, -mvel);
	}
	if (p.IsPressing(PAD_INPUT_DOWN))
	{
		vel += Vector2f(0, mvel);
	}
	if (p.IsPressing(PAD_INPUT_RIGHT))
	{
		vel += Vector2f(mvel, 0);
	}
	if (p.IsPressing(PAD_INPUT_LEFT))
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
	HP--;
	if (HP <= 0)
	{
		updater = &Player::Die;
		Die(p);
	}
	else
	{
		updater = &Player::Invincible;
	}
}

void Player::Invincible(const Peripheral & p)
{
	if (count >= 300)
	{
		count = 0;
		updater = &Player::Move;
	}
	else
	{
		count++;
	}
	Move(p);
}

void Player::Die(const Peripheral &p)
{
	vel = Vector2f(0, 0);
}

void Player::Reborn(const Peripheral & p)
{
	HP = 1;
	updater = &Player::Invincible;
}

void Player::Parasitic(const Peripheral & p, const int &eimg, const float &charasize, const ActionData &actdata)
{
	actData = actdata;
	img = eimg;
	charaSize = charasize;
}


void Player::Draw(const int& time)
{
	if (updater != &Player::Invincible)
	{
		CharacterObject::Draw(img);
	}
	else
	{
		if ((time / 5) % 2)
		{
			CharacterObject::Draw(img);
		}
	}
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
