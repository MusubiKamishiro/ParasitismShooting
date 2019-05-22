#pragma once

enum ALL_KEY
{
	PAD_A,
	PAD_B,
	PAD_Y,
	PAD_X,
	PAD_L,
	PAD_R,
	PAD_START,
	PAD_SELECT,
	PAD_UP,
	PAD_RIGHT,
	PAD_DOWN,
	PAD_LEFT,
	ALL_KEY_MAX
};

enum USE_KEY
{
	ATTACK,		// 攻撃,決定
	CANCEL,		// 寄生解除,キャンセル
	BOMB,		// ボム
	SLOW,		// ゆっくり移動
	PAUSE,		// ゲーム中断
	UP,			// ↑
	RIGHT,		// →
	DOWN,		// ↓
	LEFT,		// ←
	KEY_MAX
};



class KeyConfig
{
private:
	KeyConfig();
	KeyConfig(const KeyConfig&);
	void operator=(const KeyConfig&);
	
	int allKey[ALL_KEY_MAX];
	int defaultKey[KEY_MAX];
	int nowKey[KEY_MAX];


public:
	// ｼﾝｸﾞﾙﾄﾝｲﾝﾀｰﾌｪｰｽ
	static KeyConfig& Instance()
	{
		static KeyConfig instance;
		return instance;
	}

	~KeyConfig();

	int GetNowKey(const int& usekey);
	int GetAllKey(const int& usekey);

	void InitNowKey();

	void SetChangeKey(const int& oldkey, const int& newkey);
};

