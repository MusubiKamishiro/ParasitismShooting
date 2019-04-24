#include "Player.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../GameScreen.h"
#include <algorithm>
#include "../Shot.h"


Player::Player()
{
	img = DxLib::LoadGraph("img/title.png");
	GameScreen gscreen;
	Vector2 gssize = gscreen.GetGSSize();

	up = 0;
	right = gssize.x;
	left = 0;
	down = gssize.y;

	vel = Vector2f(0, 0);
	moveVel = 3.0;
	startPos = Vector2f(gssize.x / 2, gssize.y - 20);
	pos = startPos;
	HP = 3;
	count = 0;
	interval = 0;
	rect = Rect(15, 15, 30, 30);

	shot.reset(new Shot());
	
	updater = &Player::Move;
}

Player::~Player()
{
}

void Player::Update(const Peripheral &p)
{
	// 移動方向が決まる
	(this->*updater)(p);

	shot->Update();
	pos += vel;
	NotOutOfRange();
	ShotBullet(p);
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

void Player::ShotBullet(const Peripheral & p)
{
	if (interval % 3 == 0)
	{
		if (p.IsPressing(PAD_INPUT_2))
		{
			shot->cSHOT(pos);
		}
	}
	interval++;
}

void Player::Damage(const Peripheral & p)
{
	HP--;
	if (HP <= 0)
	{
		updater = &Player::Die;
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
	
}


void Player::Draw(Vector2f& pos, const int& time)
{
	rect.center = pos;
	if (updater != &Player::Invincible)
	{
		DxLib::DrawExtendGraph(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), img, true);
	}
	else
	{
		if ((time / 5) % 2)
		{
			DxLib::DrawExtendGraph(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), img, true);
		}
	}

	shot->Draw();
}


void Player::NotOutOfRange()
{
	// 範囲外にはいかせないぜ
	if (pos.x <= left)
	{
		pos.x = left;
	}
	else if (pos.x >= right)
	{
		pos.x = right;
	}

	if (pos.y <= up)
	{
		pos.y = up;
	}
	else if (pos.y >= down)
	{
		pos.y = down;
	}
}
