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
	count = 0;
	parasFlag = false;
	
	updater = &Player::Move;
}

Player::~Player()
{
}

void Player::Update(const Peripheral &p)
{
	// �ړ����������܂�
	(this->*updater)(p);

	pos += vel;
	NotOutOfRange();
}


void Player::Move(const Peripheral & p)
{
	vel = Vector2f();
	float mvel = charaData.moveVel;

	if (p.IsPressing(PAD_INPUT_1))
	{
		mvel = charaData.moveVel / 2;
	}

	// �{�^������������ړ�(�����8����)
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

	// �΂߈ړ��̍ۂ̓X�s�[�h����
	if ((vel.x != 0) && (vel.y != 0))
	{
		vel /= 1.4142136;
	}
}

void Player::Damage(const Peripheral & p)
{
	--charaData.HP;
	if (charaData.HP <= 0)
	{
		if (parasFlag)
		{
			charaData.HP = 1;
			parasFlag = false;
			ParasiticCancel(p);
			updater = &Player::Invincible;
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
	charaData = originData;
	updater = &Player::Invincible;
}


void Player::Parasitic(const Peripheral & p, const CharaData& cdata)
{
	parasFlag = true;

	charaData = cdata;

	count = 0;
	updater = &Player::Invincible;
}

void Player::ParasiticCancel(const Peripheral & p)
{
	charaData = originData;
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
			CharacterObject::Draw(charaData.img);
		}
	}
}


void Player::NotOutOfRange()
{
	// �͈͊O�ɂ͂������Ȃ���
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
