#pragma once

enum USE_KEY
{
	UP,			// ��
	RIGHT,		// ��
	DOWN,		// ��
	LEFT,		// ��
	ATTACK,		// �U��,����
	BOMB,		// �{��,�L�����Z��
	SLOW,		// �������ړ�
	PAUSE,		// �Q�[�����f
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
	// �ݸ���ݲ���̪��
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

