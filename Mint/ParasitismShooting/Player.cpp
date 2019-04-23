#include "Player.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "GameScreen.h"
#include <algorithm>

#include <string>

Player::Player()
{
	img = DxLib::LoadGraph("img/title.png");
	GameScreen gscreen;

	Vector2 screenSize = gscreen.GetGSSize();

	up = 0;
	right = screenSize.x;
	left = 0;
	down = screenSize.y;

	vel = Vector2(0, 0);
	moveVel = 5;
	startPos = Vector2(screenSize.x / 2, screenSize.y - 20);
	pos = startPos;
	
	updater = &Player::Move;
}

Player::~Player()
{
}

void Player::Update(const Peripheral &p)
{
	// ˆÚ“®•ûŒü‚ªŒˆ‚Ü‚é
	(this->*updater)(p);

	pos += vel;

	NotOutOfRange();
	Draw(pos);


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

	// ƒ{ƒ^ƒ“‚ð‰Ÿ‚µ‚½‚çˆÚ“®
	if (p.IsPressing(PAD_INPUT_UP))
	{
		vel += Vector2(0, -moveVel);
	}
	if (p.IsPressing(PAD_INPUT_DOWN))
	{
		vel += Vector2(0, moveVel);
	}
	if (p.IsPressing(PAD_INPUT_RIGHT))
	{
		vel += Vector2(moveVel, 0);
	}
	if (p.IsPressing(PAD_INPUT_LEFT))
	{
		vel += Vector2(-moveVel, 0);
	}
}

void Player::Shot(const Peripheral & p)
{

}


void Player::Die(const Peripheral &p)
{
}


void Player::Draw(Vector2& pos)
{
	DxLib::DrawExtendGraph(pos.x - 15, pos.y - 15, (pos.x + 15), (pos.y + 15), img, true);
}


void Player::DebugDraw()
{
}

void Player::NotOutOfRange()
{
	// ”ÍˆÍŠO‚É‚Í‚¢‚©‚¹‚È‚¢‚º
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
