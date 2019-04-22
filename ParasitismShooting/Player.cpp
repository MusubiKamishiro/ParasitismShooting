#include "Player.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Game.h"
#include <algorithm>

#include <string>

Player::Player()
{
	img = DxLib::LoadGraph("img/title.png");

	auto screenSize = Game::Instance().GetScreenSize();

	up = 50;
	right = screenSize.x - 300;
	left = 10;
	down = screenSize.y - 20;

	vel = Vector2(0, 0);
	moveVel = 5;
	moveDir = DIR_DOWN;
	oldMoveDir = moveDir;
	startPos = Vector2(100, 100);
	pos = startPos;
	
	updater = &Player::Move;
}

Player::~Player()
{
}

void Player::Update(const Peripheral &p)
{
	// “h‚è‚Â‚Ô‚µ‚Åo‚Ä‚­‚é‰æ‘œ
	//DxLib::SetDrawScreen(BG);
	//DxLib::DrawExtendGraph(0, 0, (right - left), (down - up), img, true);
	//DxLib::SetDrawScreen(DX_SCREEN_BACK);		// •`‰ææ‚ð–ß‚·

	// ˆÚ“®•ûŒü‚ªŒˆ‚Ü‚é
	(this->*updater)(p);

	oldMoveDir = moveDir;
	Vector2 oldpos = pos;
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
		moveDir = DIR_UP;
		vel += Vector2(0, -moveVel);
	}
	if (p.IsPressing(PAD_INPUT_DOWN))
	{
		moveDir = DIR_DOWN;
		vel += Vector2(0, moveVel);
	}
	if (p.IsPressing(PAD_INPUT_RIGHT))
	{
		moveDir = DIR_RIGHT;
		vel += Vector2(moveVel, 0);
	}
	if (p.IsPressing(PAD_INPUT_LEFT))
	{
		moveDir = DIR_LEFT;
		vel += Vector2(-moveVel, 0);
	}
}


void Player::Die(const Peripheral &p)
{
}


void Player::Draw(Vector2& pos)
{
	DxLib::DrawExtendGraph(pos.x, pos.y, (pos.x + 30), (pos.y + 30), img, true);
}


void Player::DebugDraw()
{
}

bool Player::NotOutOfRange()
{
	int count = 0;

	// ”ÍˆÍŠO‚É‚Í‚¢‚©‚¹‚È‚¢‚º
	if (pos.x <= left)
	{
		pos.x = left;
		count++;
	}
	else if (pos.x >= right)
	{
		pos.x = right;
		count++;
	}

	if (pos.y <= up)
	{
		pos.y = up;
		count++;
	}
	else if (pos.y >= down)
	{
		pos.y = down;
		count++;
	}

	if (count)
	{
		return true;
	}

	return false;
}
