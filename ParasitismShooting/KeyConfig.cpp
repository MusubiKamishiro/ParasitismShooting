#include "KeyConfig.h"
#include <DxLib.h>


KeyConfig::KeyConfig()
{
	// 初期設定
	defaultKey[UP]		= PAD_INPUT_UP;
	defaultKey[RIGHT]	= PAD_INPUT_RIGHT;
	defaultKey[DOWN]	= PAD_INPUT_DOWN;
	defaultKey[LEFT]	= PAD_INPUT_LEFT;
	defaultKey[ATTACK]	= PAD_INPUT_2;
	defaultKey[BOMB]	= PAD_INPUT_1;
	defaultKey[SLOW]	= PAD_INPUT_4;
	defaultKey[PAUSE]	= PAD_INPUT_8;

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

void KeyConfig::InitNowKey()
{
	// ゲーム中に使うキー, 設定で変えられる
	nowKey[UP]		= defaultKey[UP];
	nowKey[RIGHT]	= defaultKey[RIGHT];
	nowKey[DOWN]	= defaultKey[DOWN];
	nowKey[LEFT]	= defaultKey[LEFT];
	nowKey[ATTACK]	= defaultKey[ATTACK];
	nowKey[BOMB]	= defaultKey[BOMB];
	nowKey[SLOW]	= defaultKey[SLOW];
	nowKey[PAUSE]	= defaultKey[PAUSE];
}

void KeyConfig::SetChangeKey(const int& oldkey, const int& newkey)
{
	nowKey[oldkey] = defaultKey[newkey];
}
