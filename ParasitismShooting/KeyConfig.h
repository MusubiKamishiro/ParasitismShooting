#pragma once

enum USE_KEY
{
	UP,			// ↑
	RIGHT,		// →
	DOWN,		// ↓
	LEFT,		// ←
	ATTACK,		// 攻撃,決定
	BOMB,		// ボム,キャンセル
	SLOW,		// ゆっくり移動
	PAUSE,		// ゲーム中断
	KEYMAX
};



class KeyConfig
{
private:
	KeyConfig();
	KeyConfig(const KeyConfig&);
	void operator=(const KeyConfig&);
	
	int defaultKey[KEYMAX];
	int nowKey[KEYMAX];


public:
	// ｼﾝｸﾞﾙﾄﾝｲﾝﾀｰﾌｪｰｽ
	static KeyConfig& Instance()
	{
		static KeyConfig instance;
		return instance;
	}

	~KeyConfig();

	int GetNowKey(const int& usekey);

	void InitNowKey();

	// 
	void SetChangeKey(const int& oldkey, const int& newkey);
};

