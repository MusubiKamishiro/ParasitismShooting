#include "KeyConfig.h"
#include <DxLib.h>


KeyConfig::KeyConfig()
{
	allKey[PAD_A]		= PAD_INPUT_2;
	allKey[PAD_B]		= PAD_INPUT_1;
	allKey[PAD_Y]		= PAD_INPUT_4;
	allKey[PAD_X]		= PAD_INPUT_3;
	allKey[PAD_L]		= PAD_INPUT_5;
	allKey[PAD_R]		= PAD_INPUT_6;
	allKey[PAD_START]	= PAD_INPUT_8;
	allKey[PAD_SELECT]	= PAD_INPUT_7;
	allKey[PAD_UP]		= PAD_INPUT_UP;
	allKey[PAD_RIGHT]	= PAD_INPUT_RIGHT;
	allKey[PAD_LEFT]	= PAD_INPUT_LEFT;
	allKey[PAD_DOWN]	= PAD_INPUT_DOWN;

	// 初期設定
	defaultKey[ATTACK]	= allKey[PAD_A];
	defaultKey[CANCEL]	= allKey[PAD_L];
	defaultKey[BOMB]	= allKey[PAD_B];
	defaultKey[SLOW]	= allKey[PAD_Y];
	defaultKey[PAUSE]	= allKey[PAD_START];
	defaultKey[UP]		= allKey[PAD_UP];
	defaultKey[RIGHT]	= allKey[PAD_RIGHT];
	defaultKey[LEFT]	= allKey[PAD_LEFT];
	defaultKey[DOWN]	= allKey[PAD_DOWN];
	
	InitNowKey();
}

void KeyConfig::operator=(const KeyConfig &)
{
}


KeyConfig::~KeyConfig()
{
}

int KeyConfig::GetNowKey(const int & usekey)
{
	return nowKey[usekey];
}

int KeyConfig::GetAllKey(const int & usekey)
{
	return allKey[usekey];
}

void KeyConfig::InitNowKey()
{
	// ゲーム中に使うキー, 設定で変えられる
	nowKey[ATTACK]	= defaultKey[ATTACK];
	nowKey[CANCEL]	= defaultKey[CANCEL];
	nowKey[BOMB]	= defaultKey[BOMB];
	nowKey[SLOW]	= defaultKey[SLOW];
	nowKey[PAUSE]	= defaultKey[PAUSE];
	nowKey[UP]		= defaultKey[UP];
	nowKey[RIGHT]	= defaultKey[RIGHT];
	nowKey[DOWN]	= defaultKey[DOWN];
	nowKey[LEFT]	= defaultKey[LEFT];
}

void KeyConfig::SetChangeKey(const int& oldkey, const int& newkey)
{
	nowKey[oldkey] = allKey[newkey];
}
