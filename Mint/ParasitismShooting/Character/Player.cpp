#include "Player.h"
#include <DxLib.h>
#include <algorithm>
#include "../Peripheral.h"
#include "../GameScreen.h"
#include "../Shot.h"


Player::Player()
{
	ReadActionFile("action/player.act");
	ChangeAction("Idle");
	// c_str()	末尾がNULLでなければNULLを足して、文字列の最初の文字を指すポインタを返す
	img = DxLib::LoadGraph(actData.imgFilePath.c_str());

	//img = DxLib::LoadGraph("img/title.png");
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
	HP = 3;
	count = 0;
	interval = 0;
	//rect = Rect(pos.x, pos.y, 30, 30);

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
			shot->setBullet(pos, 0, 5, 0, 4, SHOT_PTN::NORMAL, SHOTER::PLAYER);
		}
		if (p.IsPressing(PAD_INPUT_4))
		{
			shot->setBullet(pos, 0, 5, 0, 3, SHOT_PTN::SHOTGUN, SHOTER::PLAYER);
		}
		if (p.IsPressing(PAD_INPUT_5))
		{
			shot->setBullet(pos, 0, 5, 0, 1, SHOT_PTN::TRACKING, SHOTER::PLAYER);
		}
		if (p.IsPressing(PAD_INPUT_6))
		{
			shot->setBullet(pos, 0, 5, 0, 100, SHOT_PTN::RADIATION, SHOTER::PLAYER);
		}
		if (p.IsPressing(PAD_INPUT_10))
		{
			shot->setBullet(pos, 0, 5, 0, 100, SHOT_PTN::RANDOM, SHOTER::PLAYER);
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
		
	shot->Draw();
}

int& Player::GetHP()
{
	return HP;
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
