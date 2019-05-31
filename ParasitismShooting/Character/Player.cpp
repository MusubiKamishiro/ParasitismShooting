#include "Player.h"
#include <DxLib.h>
#include <algorithm>
#include "../Peripheral.h"
#include "../GameScreen.h"
#include "../Sound.h"

void Player::Init()
{
	// プレイヤー寄生前の基本データ
	ReadActionFile("action/player.act");
	ChangeAction("Idle");
	SetCharaSize(0.1f);
	charaData.img = DxLib::LoadGraph(charaData.actData.imgFilePath.c_str());
	charaData.HP = 1;
	charaData.moveVel = 3.0;
	charaData.shotType = "Weak";
	//charaData.shotTypeSub = "Shotgun";
	//charaData.shotLevel = 7;
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
	pinchFlag = false;
}

Player::Player()
{
	Sound::Instance().AddSE("parascancel.mp3");
	Sound::Instance().AddSE("paras.mp3");
	Sound::Instance().AddSE("damage.mp3");

	Init();

	parasFlag = false;
	updater = &Player::Move;
}

Player::Player(const CharaData& cdata)
{
	Init();

	// 前のステージでの最後の姿を持ってくる
	charaData = cdata;
	charaData.shotType == originData.shotType ? parasFlag = false : parasFlag = true;

	updater = &Player::Move;
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
		Sound::Instance().PlaySE("damage");
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
	Sound::Instance().PlaySE("paras");

	parasFlag = true;

	charaData = cdata;
	charaData.HP = cdata.HP / 3;
	if (charaData.HP > 7)
	{
		charaData.HP = 7;
	}

	charaData.shotLevel = cdata.shotLevel;

	icount = 0;
	updater = &Player::Invincible;
}

void Player::ParasiticCancel(const Peripheral & p)
{
	Sound::Instance().PlaySE("parascancel");

	DxLib::StartJoypadVibration(DX_INPUT_PAD1, 1000, 1000);
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
}

void Player::ParasDraw(const int & time)
{
	if ((time / 3) % 2)
	{
		auto& actInfo = originData.actData.animInfo["Idle"];
		auto& cut = actInfo.cuts[0];
		auto& rc = cut.rect;

		DxLib::DrawRectRotaGraph2F(pos.x, pos.y, rc.Left(), rc.Top(), rc.Width(), rc.Height(), cut.center.x, cut.center.y, originData.charaSize, 0.0, originData.img, true, false);
	}
	else
	{
		CharacterObject::Draw(charaData.img);
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
