#pragma once

enum USE_KEY
{
	UP,			// Ŗ
	RIGHT,		// Ø
	DOWN,		// «
	LEFT,		// ©
	ATTACK,		// U,č
	BOMB,		// {,LZ
	SLOW,		// äĮ­čŚ®
	PAUSE,		// Q[f
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
	// ¼ŻøŽŁÄŻ²ŻĄ°ĢŖ°½
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

