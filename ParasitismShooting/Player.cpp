#include "Player.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "GameScreen.h"
#include <algorithm>
#include "Shot.h"
#include <string>

Player::Player()
{
	img = DxLib::LoadGraph("img/title.png");
	GameScreen gscreen;

	Vector2 gssize = gscreen.GetGSSize();

	up = 15;
	right = gssize.x - 15;
	left = 15;
	down = gssize.y - 15;

	vel = Vector2(0, 0);
	moveVel = 3.0;
	startPos = Vector2(gssize.x / 2, gssize.y - 20);
	pos = startPos;

	shot.reset(new Shot());

	
	updater = &Player::Move;

	cnt = 0;
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
//	Draw(pos);


#ifdef _DEBUG
	DebugDraw();

#endif // _DEBUG
}

Vector2 Player::GetPos() const
{
	return pos;
}


void Player::Move(const Peripheral & p)
{
	vel = Vector2();
	float mvel = moveVel;

	if (p.IsPressing(PAD_INPUT_1))
	{
		mvel = moveVel / 2;
	}

	// ボタンを押したら移動(今回は8方向)
	if (p.IsPressing(PAD_INPUT_UP))
	{
		vel += Vector2(0, -mvel);
	}
	if (p.IsPressing(PAD_INPUT_DOWN))
	{
		vel += Vector2(0, mvel);
	}
	if (p.IsPressing(PAD_INPUT_RIGHT))
	{
		vel += Vector2(mvel, 0);
	}
	if (p.IsPressing(PAD_INPUT_LEFT))
	{
		vel += Vector2(-mvel, 0);
	}

	// 斜め移動の際はスピード調整
	if ((vel.x != 0) && (vel.y != 0))
	{
		vel /= 1.4142136;
	}
}

void Player::ShotBullet(const Peripheral & p)
{
	cnt++;
	if (cnt % 3 == 0)
	{
		if (p.IsPressing(PAD_INPUT_2))
		{
			shot->cSHOT(pos);
		}
	}
}

void Player::Die(const Peripheral &p)
{
}


void Player::Draw(Vector2& pos)
{
	DxLib::DrawExtendGraph(pos.x - 15, pos.y - 15, (pos.x + 15), (pos.y + 15), img, true);

	shot->Draw();
}


void Player::DebugDraw()
{
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
